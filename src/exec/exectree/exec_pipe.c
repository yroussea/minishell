/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 16:57:05 by yroussea          #+#    #+#             */
/*   Updated: 2024/03/22 18:41:33 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	wait_all(t_stack_id **stk, int checkpoint)
{
	t_stack_id	*tmp;
	int			pid;

	tmp = *stk;
	while (stk && tmp)
	{
		pid = stk_pid_pop(stk);
		ft_printf_fd(2, "PID: %d checkpoint:%d\n", pid, checkpoint);
		if (pid == -1 || pid == checkpoint)
			break ;
		waitpid(pid, NULL, 0);
	}
}

t_bool	exec_pipe(t_node *node, t_bool from_pipe, t_data_stk *stks, t_fds fds)
{
	int			fd_pipe[2];
	int			pid;
	t_stack_id *tmp;

	tmp = *stks->pids;
	if (tmp)
		pid = tmp->pid;
	else
		pid = -1;
	ft_printf_fd(2, "PID: %d\n", pid);
	if (ft_pipe(fd_pipe) < 0)
		return (ERROR);
	ft_stk_pipe_add(stks->pipes, fd_pipe);
	fds = (t_fds) {0, fd_pipe[1]};
	exec_tree(node->left, TRUE, stks, fds);
	fds = (t_fds) {fd_pipe[0], 1};
	exec_tree(node->right, TRUE, stks, fds);
	if (!from_pipe) //attention car:  cmd <- pipe -> et -> pipeline (enum dc)
		wait_all(stks->pids, pid);
	if (ft_close(2, fd_pipe[0], fd_pipe[1]) < 0)
		return (ERROR);
	return (TRUE);
}
