/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basverdi <basverdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 16:56:14 by yroussea          #+#    #+#             */
/*   Updated: 2024/03/26 16:57:39 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <unistd.h>

void	ft_close_command(t_node *node)
{
	if (!node)
		return ;
	if (node->infile > 2)
		close(node->infile);
	if (node->outfile > 2)
		close(node->outfile);
}

t_bool	all_redir_cmd(t_lst_redir *redir, t_fds fds)
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
		{
			if (fds_in != STDIN_FILENO)
				ft_close(1, fds_in);
			fds_in = redir->heredoc_fd;
			if (fds_in == -1)
				break ;
		}
		if (redir->type == DIRE_IN)
		{
			if (fds_in != STDIN_FILENO)
				ft_close(1, fds_in);
			fds_in = open(redir->file, 0);
			if (fds_in == -1)
				break ;
		}
		if (redir->type == ADD)
		{
			if (fds_out != STDOUT_FILENO)
				ft_close(1, fds_out);
			fds_out = open(redir->file, O_CREAT | O_WRONLY | O_APPEND, 0664);
			if (fds_out == -1)
				break ;
		}
		if (redir->type == DIRE_OUT)
		{
			if (fds_out != STDOUT_FILENO)
				ft_close(1, fds_out);
			fds_out = open(redir->file, 577, 0664);
			if (fds_out == -1)
				break ;
		}
		if (redir->type == DIRE_TWO)
		{
			if (fds_error != STDERR_FILENO)
				ft_close(1, fds_error);
			fds_error = open(redir->file, 577, 0664);
			if (fds_error == -1)
				break ;
		}
		redir = redir->next;
	}
	if (fds_error == -1 || fds_in == -1 || fds_out == -1)
		return (FALSE);
	//ft_printf_fd(2, "FDS: %d %d %d %d\n", fds_in, fds_out, fds.in, fds.out);
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

t_bool	exec_cmd(t_node *node, t_bool from_pipe, t_data_stk *stks, t_fds fds)
{
	int			pid;
	char		**envp_char;
	char		*full_cmd;
	t_builtin	builtin_type;

	(void)from_pipe;
	//unquoting :)
	parse_quote(node);
	
	//difference buildin et cmd
	if (is_builtin(node))
		return (ft_exec_builtin(node, from_pipe, stks, fds));
	full_cmd = get_access(*(node->envp), node->cmd);
	free(node->cmd);
	if (full_cmd)
	{
		pid = ft_fork();
		if (pid < 0)
			return (ERROR);
		if (pid == 0)
		{
			envp_char = envp_to_char(*node->envp);
			if (envp_char)
			{
				if (all_redir_cmd(node->redir, fds))
				{
					ft_close_pipe(stks->pipes);
					execve(full_cmd, node->args, envp_char);
				}
				else 
					ft_close_pipe(stks->pipes);
				free(full_cmd);
			}
			ft_magic_free("%2 %2", node->args, envp_char);
			///free all
			exit(1);
		}
		ft_stk_pid_add(stks->pids, pid);
		ft_magic_free("%1 %2", full_cmd, node->args);
		return (TRUE);
	}
	ft_free_split(node->args);
	//close cmd redir
	return (ERROR);
}
