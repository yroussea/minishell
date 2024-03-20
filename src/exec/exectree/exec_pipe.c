/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 16:57:05 by yroussea          #+#    #+#             */
/*   Updated: 2024/03/20 20:23:56 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	wait_all(t_stack_id **stk, int checkpoint)
{
	t_stack_id	*tmp;

	tmp = *stk;
	while (tmp)
	{
		//wait ce qu'il faut (jusqua un pid famillier)
		tmp = tmp->next;
	}
	(void)checkpoint;
}

t_bool	exec_pipe(t_node *node, t_bool from_pipe, t_data_stk *stks, t_fds fds)
{
	int		fd_pipe[2];
	int		pid;

	pid = stk_pid_pop(stks->pids);
	if (ft_pipe(fd_pipe) < 0)
		return (ERROR);
	ft_stk_pipe_add(stks->pipes, fd_pipe);
	//fork un fils inutile pour savoir jusqua ou wait?
	fds.in = 0;
	fds.out = fd_pipe[1];
	exec_tree(node->left, TRUE, stks, fds);
	fds.in = fd_pipe[0];
	fds.out = 1;
	exec_tree(node->right, TRUE, stks, fds);
	if (!from_pipe) //attention car:  cmd <- pipe -> et -> pipeline (enum dc)
		wait_all(stks->pids, pid);
	if (ft_close(2, fd_pipe[0], fd_pipe[1]) < 0)
		return (ERROR);
	return (TRUE);
}
