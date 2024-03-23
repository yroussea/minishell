/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 16:57:05 by yroussea          #+#    #+#             */
/*   Updated: 2024/03/23 15:55:31 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	close_pipes(t_stack_pipe **stk_pipe)
{
	t_stack_pipe	*stk;

	stk = stk_pipe_pop(stk_pipe);
	if (!stk)
		return ;
	if (stk->pipe[0] > 2)
		ft_close(1, stk->pipe[0]);
	if (stk->pipe[1] > 2)
		ft_close(1, stk->pipe[1]);
	free(stk);
}


void	wait_all(t_stack_id **stk, int checkpoint)
{
	int			pid;

	while (stk && *stk)
	{
		pid = stk_pid_pop(stk);
		if (pid == -1 || pid == checkpoint)
			break ;
		waitpid(pid, NULL, 0);
	}
	//ft_printf_fd(2, "ALL PID WAITED");
}

t_bool	exec_pipe(t_node *node, t_bool from_pipe, t_data_stk *stks, t_fds fds)
{
	int			fd_pipe[2];
	t_fds		tmp_fds;
	int			pid;
	t_stack_id *tmp;

	tmp = *stks->pids;
	if (tmp)
		pid = tmp->pid;
	else
		pid = -1;
//	ft_printf_fd(2, "PID: %d\n", pid);
	if (ft_pipe(fd_pipe) < 0)
		return (ERROR);
	ft_stk_pipe_add(stks->pipes, fd_pipe);
	tmp_fds = (t_fds) {fds.in, fd_pipe[1]};
	exec_tree(node->left, TRUE, stks, tmp_fds);
	tmp_fds = (t_fds) {fd_pipe[0], fds.out};
	exec_tree(node->right, TRUE, stks, tmp_fds);
	close_pipes(stks->pipes);
	if (!from_pipe) //attention car:  cmd <- pipe -> et -> pipeline (enum dc)
		wait_all(stks->pids, pid);
	return (TRUE);
}
