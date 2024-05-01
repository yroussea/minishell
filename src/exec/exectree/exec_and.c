/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_and.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basverdi <basverdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 16:56:19 by yroussea          #+#    #+#             */
/*   Updated: 2024/05/01 16:50:45 by basverdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

extern int	g_exitcode;

t_bool	exec_and(t_node *node, t_from_pipe from_pipe, t_data_stk *stks, t_fds \
	fds)
{
	int	pid;
	int	tmp_err;

	if (fds.in != 0)
		ft_dup2(fds.in, STDIN_FILENO);
	if (fds.out != 1)
		ft_dup2(fds.out, STDOUT_FILENO);
	exec_tree(node->left, from_pipe, stks, fds);
	pid = stk_pid_pop(stks->pids);
	if (pid != -1)
	{
		ft_close_pipe((stks)->pipes);
		waitpid(pid, &tmp_err, 0);
		if (tmp_err == 2)
			g_exitcode = 130;
		else
			g_exitcode = WEXITSTATUS(tmp_err);
	}
	if (g_exitcode == 0)
		exec_tree(node->right, from_pipe, stks, fds);
	return (TRUE);
}
