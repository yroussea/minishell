/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basverdi <basverdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 16:56:14 by yroussea          #+#    #+#             */
/*   Updated: 2024/04/18 12:09:16 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

extern int	g_exitcode;

void	ft_close_command(t_node *node)
{
	if (!node)
		return ;
	if (node->infile > 2)
		close(node->infile);
	if (node->outfile > 2)
		close(node->outfile);
}

t_bool	no_replace_heredoc(char *str)
{
	while (str && *str)
	{
		if (*str == 34 && *str == 39)
			return (FALSE);
		str += 1;
	}
	return (TRUE);
}

int	redir_heredoc(int fds_in, t_lst_redir *redir, t_lst_envp *lst_envp)
{
	if (fds_in != STDIN_FILENO)
		ft_close(1, fds_in);
	fds_in = redir->heredoc_fd;
	if (fds_in == -1)
		return (-1);
	if (no_replace_heredoc(redir->file) == FALSE)
		fds_in = heredoc_reopen(fds_in, lst_envp);
	return (fds_in);
}

int	redir_infile(int fds_in, t_lst_redir *redir)
{
	if (fds_in != STDIN_FILENO)
		ft_close(1, fds_in);
	fds_in = open(redir->file, 0); //cas d'erreur
	return (fds_in);
}

int	redir_add(int fds_out, t_lst_redir *redir)
{
	if (fds_out != STDOUT_FILENO)
		ft_close(1, fds_out);
	fds_out = open(redir->file, O_CREAT | O_WRONLY | O_APPEND, 0664);
//cas d'erreur
	return (fds_out);
}

int	redir_out(int fds_out, t_lst_redir *redir)
{
	if (fds_out != STDOUT_FILENO)
		ft_close(1, fds_out);
	fds_out = open(redir->file, 577, 0664);//cas d'erreur
	return (fds_out);
}

int	redir_error(int fds_error, t_lst_redir *redir)
{
	if (fds_error != STDERR_FILENO)
		ft_close(1, fds_error);
	fds_error = open(redir->file, 577, 0664);//cas d'erreur
	return (fds_error);
}

void	replace_fds(int fds_in, int fds_out, int fds_error, t_fds fds)
{
	if (fds_in != STDIN_FILENO)
	{
		ft_dup2(fds_in, STDIN_FILENO);
		ft_close(1, fds_in);
	}
	else if (fds.in != STDIN_FILENO)
		ft_dup2(fds.in, STDIN_FILENO);
	if (fds_out != STDOUT_FILENO)
	{
		ft_dup2(fds_out, STDOUT_FILENO);
		ft_close(1, fds_out);
	}
	else if (fds.out != STDOUT_FILENO)
		ft_dup2(fds.out, STDOUT_FILENO);
	if (fds_error != STDERR_FILENO)
	{
		ft_dup2(fds_error, STDERR_FILENO);
		ft_close(1, fds_error);
	}
}

t_bool	all_redir_builtin(t_node *node, t_lst_redir *redir, t_lst_envp \
	*lst_envp)
{
	int	fds_error;
	int	fds_in;
	int	fds_out;

	fds_in = 0;
	fds_out = 1;
	fds_error = 2;
	while (redir)
	{
		if (redir->type == HEREDOC)
			fds_in = redir_heredoc(fds_in, redir, lst_envp);
		if (redir->type == DIRE_IN)
			fds_in = redir_infile(fds_in, redir);
		if (redir->type == ADD)
			fds_out = redir_add(fds_out, redir);
		if (redir->type == DIRE_OUT)
			fds_out = redir_out(fds_out, redir);
		if (redir->type == DIRE_TWO)
			fds_error = redir_error(fds_error, redir);
		if (fds_error == -1 || fds_in == -1 || fds_out == -1)
			return (FALSE); //msg
		redir = redir->next;
	}
	node->infile = fds_in;
	node->outfile = fds_out;
	node->errorfile = fds_error;
	return (TRUE);
}

t_bool	all_redir_cmd(t_lst_redir *redir, t_fds fds, t_lst_envp *lst_envp)
{
	int	fds_error;
	int	fds_in;
	int	fds_out;

	fds_in = 0;
	fds_out = 1;
	fds_error = 2;
	while (redir)
	{
		if (redir->type == HEREDOC)
			fds_in = redir_heredoc(fds_in, redir, lst_envp);
		/*
		 * remplacement var env, et unquoting,
		 * si var env, ->accepte pas les espaces,
		 * sinon -> espace doit etre dans le nom
		*/
		if (redir->type == DIRE_IN)
			fds_in = redir_infile(fds_in, redir);
		if (redir->type == ADD)
			fds_out = redir_add(fds_out, redir);
		if (redir->type == DIRE_OUT)
			fds_out = redir_out(fds_out, redir);
		if (redir->type == DIRE_TWO)
			fds_error = redir_error(fds_error, redir);
		if (fds_error == -1 || fds_in == -1 || fds_out == -1)
			return (FALSE); //msg
		redir = redir->next;
	}
	replace_fds(fds_in, fds_out, fds_error, fds);
	return (TRUE);
}

void	parse_quote(t_node *node)
{
	int		i;
	char	**result;

	i = ft_str_str_len(node->args);
	result = ft_calloc(sizeof(char *), i + 1);
	i = 0;
	while (result && node->args && *(node->args + i))
	{
		result[i] = ft_unquote(*(node->args + i), *(node->envp));
		if (!result[i])
		{
			ft_free_split(result);
			node->cmd = ft_strdup(*node->args);
			return ;
		}
		i += 1;
	}
	if (!result)
	{
		node->cmd = ft_strdup(*node->args);
		return ;
	}
	node->args = result;
	node->cmd = ft_strdup(*result);
}

void	exit_cmd(char *full_cmd, t_node *node, char **envp)
{
	free(full_cmd);
	ft_magic_free("%2 %2", node->args, envp);
	ft_get_envp(NULL, FALSE, TRUE);
	ft_get_root(NULL, FALSE, TRUE);
	ft_get_lsts(NULL, NULL, FALSE, TRUE);
	ft_get_stks(NULL, FALSE, TRUE);
	clear_history();
	exit(1);
}

void	child_exec_cmd(char *full_cmd, t_node *node, t_fds fds, t_data_stk \
	*stks)
{
	char	**envp_char;

	envp_char = envp_to_char(*node->envp);
	if (envp_char)
	{
		if (all_redir_cmd(node->redir, fds, *node->envp))
		{
			ft_close_pipe(stks->pipes);
			close_heredoc(ft_get_root(NULL, FALSE, FALSE));
			execve(full_cmd, node->args, envp_char);
		}
		else
			ft_close_pipe(stks->pipes); //close redir faileed?
		//exit with good status?
	}
	exit_cmd(full_cmd, node, envp_char);
}

void	fake_pid(int exit_code, t_data_stk *stks)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		ft_close_pipe(stks->pipes);
		ft_get_envp(NULL, FALSE, TRUE);
		ft_get_root(NULL, FALSE, TRUE);
		ft_get_lsts(NULL, NULL, FALSE, TRUE);
		ft_get_stks(NULL, FALSE, TRUE);
		clear_history();
		exit(exit_code);
	}
	if (pid > 0)
		ft_stk_pid_add(stks->pids, pid);
}

t_bool	exec_cmd(t_node *node, t_from_pipe from_pipe, t_data_stk *stks, t_fds \
	fds)
{
	int			pid;
	char		*full_cmd;

	parse_quote(node);
	if (node->cmd && is_builtin(node))
		return (ft_exec_builtin(node, from_pipe, stks, fds));
	full_cmd = get_access(*(node->envp), node->cmd);
	free(node->cmd);
	if (full_cmd)
	{
		pid = ft_fork();
		if (pid == 0)
			child_exec_cmd(full_cmd, node, fds, stks);
		if (pid > 0)
			ft_stk_pid_add(stks->pids, pid);
		ft_magic_free("%2 %1", node->args, full_cmd);
		return (TRUE);
	}
	all_redir_builtin(node, node->redir, *node->envp);
	close_redir_builtin(node);
	ft_free_split(node->args);
	fake_pid(g_exitcode, stks);
	return (ERROR);
}
