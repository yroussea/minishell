/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basverdi <basverdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:46:08 by yroussea          #+#    #+#             */
/*   Updated: 2024/04/10 18:29:26 by yroussea         ###   ########.fr       */
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
	if (!ft_strncmp(node->cmd, "cat", 4))
		return (CAT);
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

void	exec_builtin(char *cmd, t_node *node)
{
	if (!ft_strncmp(cmd, "exit", 4))
	{
		ft_exit(node);
	}
	if (!ft_strncmp(cmd, "pwd", 4))
	{
		ft_pwd(node);
	}
	if (!ft_strncmp(cmd, "cd", 3))
	{
	}
	if (!ft_strncmp(cmd, "cat", 4))
	{
	}
	if (!ft_strncmp(cmd, "unset", 6))
	{
	}
	if (!ft_strncmp(cmd, "export", 7))
	{
	}
	if (!ft_strncmp(cmd, "env", 4))
	{
		ft_env(node);
	}
	if (!ft_strncmp(cmd, "echo", 5))
	{
		ft_echo(node);
	}
}

t_bool	ft_exec_builtin(t_node *node, t_bool from_pipe, \
	t_data_stk *stks, t_fds fds)
{
	int	pid;

	if (from_pipe)
	{
		pid = ft_fork();
		if (pid < 0)
			return (ERROR);
		if (pid == 0)
		{
			if (all_redir_cmd(node->redir, fds)) //?
			{
				ft_close_pipe(stks->pipes);
				close_heredoc(ft_get_root(NULL, FALSE, FALSE));
				//exec node->cmd, node->args
				exec_builtin(node->cmd, node);
			}
			ft_magic_free("%1 %2", node->cmd, node->args);
			exit(1);
		}
		ft_stk_pid_add(stks->pids, pid);
		ft_magic_free("%1 %2", node->cmd, node->args);
		return (TRUE);
	}
	else
	{
		exec_builtin(node->cmd, node);
		// exec
	}
	ft_magic_free("%1 %2", node->cmd, node->args);
	return (ERROR);
}