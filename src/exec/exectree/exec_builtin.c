/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basverdi <basverdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:46:08 by yroussea          #+#    #+#             */
/*   Updated: 2024/04/16 17:16:10 by basverdi         ###   ########.fr       */
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
		ft_export(node, NULL);
	if (!ft_strncmp(cmd, "env", 4))
		ft_env(node);
	if (!ft_strncmp(cmd, "echo", 5))
		ft_echo(node);
}

void	close_redir_builtin(t_node *node)
{
	if (node->infile != 0)
		ft_close(1, node->infile);
	if (node->outfile != 1)
		ft_close(1, node->outfile);
	if (node->errorfile != 2)
		ft_close(1, node->errorfile);
}

void	exit_builtin(t_node *node, int exit_code)
{
	ft_magic_free("%1 %2", node->cmd, node->args);
	ft_get_envp(NULL, FALSE, TRUE);
	ft_get_root(NULL, FALSE, TRUE);
	ft_get_lsts(NULL, NULL, FALSE, TRUE);
	ft_get_stks(NULL, FALSE, TRUE);
	clear_history();
	exit(exit_code);
}

extern int g_exitcode;

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
		{
			node->infile = fds.in;
			node->outfile = fds.out;
			if (all_redir_builtin(node, node->redir, *node->envp)) //?
			{
				ft_close_pipe(stks->pipes);
				close_heredoc(ft_get_root(NULL, FALSE, FALSE));
				//exec node->cmd, node->args
				exec_builtin(node->cmd, node, TRUE);
				exit_builtin(node, 0);
			}
			exit_builtin(node, 1);
		}
		ft_stk_pid_add(stks->pids, pid);
		ft_magic_free("%1 %2", node->cmd, node->args);
		return (TRUE);
	}
	else
	{
		g_exitcode = all_redir_builtin(node, node->redir, *node->envp);
		if (g_exitcode)
			exec_builtin(node->cmd, node, FALSE);
		close_redir_builtin(node);
	}
	ft_magic_free("%1 %2", node->cmd, node->args);
	return (TRUE);
}
