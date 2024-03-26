/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basverdi <basverdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:46:08 by yroussea          #+#    #+#             */
/*   Updated: 2024/03/26 17:45:45 by basverdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_builtin is_builtin(t_node *node)
{
	if (!ft_strncmp(node->cmd, "exit", 5))
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
	return (NOT_A_BUILTIN);
}

t_bool ft_exec_builtin(t_node *node, t_bool from_pipe, t_data_stk *stks, t_fds fds)
{
	int pid;

	(void)fds;
	if (from_pipe)
	{
		pid = ft_fork();
		if (pid < 0)
			return (ERROR);
		if (pid == 0)
		{
			// all_redir
			// closepipe
			ft_magic_free("%1 %2", node->cmd, node->args);
			exit(1);
		}
		ft_stk_pid_add(stks->pids, pid);
		ft_magic_free("%1 %2", node->cmd, node->args);
		return (TRUE);
	}
	// exec
	return (TRUE);
}
