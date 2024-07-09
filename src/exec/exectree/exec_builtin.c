/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basverdi <basverdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:46:08 by yroussea          #+#    #+#             */
/*   Updated: 2024/07/09 09:16:14 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_builtin	is_builtin(t_node *node)
{
	if (!ft_strncmp(node->cmd, "exit", 4))
		return (EXIT);
	if (!ft_strncmp(node->cmd, "pwd", 4))
		return (PWD);
	if (!ft_strncmp(node->cmd, "cd", 3))
		return (CD);
	if (!ft_strncmp(node->cmd, "unset", 6))
		return (UNSET);
	if (!ft_strncmp(node->cmd, "export", 7))
		return (EXPORT);
	if (!ft_strncmp(node->cmd, "env", 4))
		return (ENV);
	if (!ft_strncmp(node->cmd, "echo", 5))
		return (ECHO);
	return (NOT_A_BUILTIN);
}

void	exec_builtin(char *cmd, t_node *node, t_bool from_pipe)
{
	if (!ft_strncmp(cmd, "exit", 4))
		ft_exit(node, from_pipe);
	if (!ft_strncmp(cmd, "pwd", 4))
		ft_pwd(node);
	if (!ft_strncmp(cmd, "cd", 3))
		ft_cd(node);
	if (!ft_strncmp(cmd, "unset", 6))
		ft_unset(node, NULL);
	if (!ft_strncmp(cmd, "export", 7))
		ft_export(node);
	if (!ft_strncmp(cmd, "env", 4))
		ft_env(node, NULL, 0);
	if (!ft_strncmp(cmd, "echo", 5))
		ft_echo(node);
}

void	exit_builtin(t_node *node, int exit_code)
{
	ft_magic_free("%1 %2", node->cmd, node->args);
	ft_get_envp(NULL, FALSE, TRUE);
	ft_get_root(NULL, FALSE, TRUE);
	ft_get_lsts(NULL, NULL, FALSE, TRUE);
	ft_get_stks(NULL, FALSE, TRUE);
	rl_clear_history();
	exit(exit_code);
}

void	child_builtin(t_node *node, t_data_stk *stks, t_fds fds)
{
	node->infile = fds.in;
	node->outfile = fds.out;
	node->errorfile = 2;
	if (all_redir_builtin(node, node->redir, *node->envp))
	{
		close_heredoc(ft_get_root(NULL, FALSE, FALSE));
		exec_builtin(node->cmd, node, TRUE);
		ft_close_pipe(stks->pipes);
		close_redir_builtin(node);
		exit_builtin(node, 0);
	}
	exit_builtin(node, 1);
}

t_bool	ft_exec_builtin(t_node *node, t_from_pipe from_pipe, \
	t_data_stk *stks, t_fds fds)
{
	int	pid;

	if (from_pipe != NO_PIPE)
	{
		pid = ft_fork();
		if (pid < 0)
			return (ERROR);
		if (pid == 0)
			child_builtin(node, stks, fds);
		ft_stk_pid_add(stks->pids, pid);
		ft_magic_free("%1 %2", node->cmd, node->args);
		return (TRUE);
	}
	else
	{
		get_set_exit_code(1 - all_redir_builtin(node, node->redir, \
			*node->envp), TRUE);
		if (!get_set_exit_code(0, FALSE))
			exec_builtin(node->cmd, node, FALSE);
		close_redir_builtin(node);
	}
	ft_magic_free("%1 %2", node->cmd, node->args);
	return (TRUE);
}
