/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basverdi <basverdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 16:56:14 by yroussea          #+#    #+#             */
/*   Updated: 2024/06/11 05:55:27 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

extern int	g_exitcode;

void	parse_quote(t_node *node, int j, int i)
{
	char	**result;

	result = ft_calloc(sizeof(char *), ft_str_str_len(node->args) + 1);
	while (result && node->args && *(node->args + j))
	{
		result[i] = ft_unquote(*(node->args + j), *(node->envp));
		if (result[i])
			i += 1;
		j += 1;
	}
	if (!result)
		node->cmd = ft_strdup(*node->args);
	if (!result)
		return ;
	node->args = result;
	if (!*result)
		node->cmd = ft_strdup("");
	else
		node->cmd = ft_strdup(*(result));
}

void	exit_cmd(char *full_cmd, t_node *node, char **envp, int exitcode)
{
	free(full_cmd);
	ft_magic_free("%2 %2", node->args, envp);
	ft_get_envp(NULL, FALSE, TRUE);
	ft_get_root(NULL, FALSE, TRUE);
	ft_get_lsts(NULL, NULL, FALSE, TRUE);
	ft_get_stks(NULL, FALSE, TRUE);
	rl_clear_history();
	exit(exitcode);
}

void	child_exec_cmd(char *full_cmd, t_node *node, t_fds fds, t_data_stk \
	*stks)
{
	char	**envp_char;

	envp_char = envp_to_char(*node->envp);
	signal(SIGINT, handler_fail);
	if (envp_char)
	{
		if (all_redir_cmd(node->redir, fds, *node->envp))
		{
			ft_close_pipe(stks->pipes);
			close_heredoc(ft_get_root(NULL, FALSE, FALSE));
			execve(full_cmd, node->args, envp_char);
		}
		else
			ft_close_pipe(stks->pipes);
		g_exitcode = 1;
	}
	exit_cmd(full_cmd, node, envp_char, g_exitcode);
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
		rl_clear_history();
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

	parse_quote(node, 0, 0);
	if (node->cmd && is_builtin(node))
		return (ft_exec_builtin(node, from_pipe, stks, fds));
	full_cmd = get_access(*(node->envp), node->cmd);
	free(node->cmd);
	if (full_cmd)
	{
		signal(SIGINT, SIG_IGN);
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
