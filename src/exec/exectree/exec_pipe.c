/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basverdi <basverdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 16:57:05 by yroussea          #+#    #+#             */
/*   Updated: 2024/04/01 03:32:47 by yroussea         ###   ########.fr       */
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
	int	pid;

	while (stk && *stk)
	{
		pid = stk_pid_pop(stk);
		if (pid == -1 || pid == checkpoint)
			break ;
		waitpid(pid, NULL, 0);
	}
}

t_bool	exec_pipe_under_pipe(t_node *node, t_data_stk *stks, t_fds fds)
{
	int			fd_pipe[2];
	int			fd_pipe_return[2];
	t_fds		tmp_fds;

	if (ft_pipe(fd_pipe) < 0)
		return (FALSE);
	ft_stk_pipe_add(stks->pipes, fd_pipe);

	tmp_fds = (t_fds){fds.in, fd_pipe[1]};
	exec_tree(node->left, TRUE, stks, tmp_fds);
	
	if (ft_pipe(fd_pipe_return) < 0)
		return (FALSE);
	tmp_fds = (t_fds){fd_pipe[0], fd_pipe_return[1]};
	exec_tree(node->right, TRUE, stks, tmp_fds);

	close_pipes(stks->pipes);

	ft_stk_pipe_add(stks->pipes, fd_pipe_return);

	return (TRUE);
}

t_bool	exec_pipe_over_pipe(t_node *node, t_data_stk *stks, t_fds fds)
{
	int				fd_pipe[2];
	int				fd_pipe_return[2];
	t_fds			tmp_fds;
	t_stack_pipe	*tmp_stk;

	if (node->left->left->type != PIPE)
		exec_pipe_under_pipe(node->left, stks, fds);
	else
		exec_pipe_over_pipe(node->left, stks, fds);
	tmp_stk = stk_pipe_pop(stks->pipes);
	fd_pipe[0] = tmp_stk->pipe[0];
	fd_pipe[1] = tmp_stk->pipe[1];
	free(tmp_stk);

	if (ft_pipe(fd_pipe_return) < 0)
		return (FALSE);
	tmp_fds = (t_fds){fd_pipe[0], fd_pipe_return[1]};
	exec_tree(node->right, TRUE, stks, tmp_fds);
	ft_close(2, fd_pipe[0], fd_pipe[1]);
	ft_stk_pipe_add(stks->pipes, fd_pipe_return);
	return (TRUE);
}

t_bool	exec_pipe(t_node *node, t_bool from_pipe, t_data_stk *stks, t_fds fds)
{
	int			fd_pipe[2];
	t_fds		tmp_fds;
	int			pid;
	t_stack_id	*tmp;

	//si pipe->pipe->cmd => exec_pipe_under_pipe
	//si pipe->pipe->pipe->cmd => exec_pipe_under_pipe -> exec_pipe_under_pipe
	////
	tmp = *stks->pids;
	if (tmp)
		pid = tmp->pid;
	else
		pid = -1;
	if (node->left->type == PIPE)
		exec_pipe_over_pipe(node, stks, fds);
	else
	{
		if (ft_pipe(fd_pipe) < 0)
			return (ERROR);
		ft_stk_pipe_add(stks->pipes, fd_pipe);
		tmp_fds = (t_fds){fds.in, fd_pipe[1]};
		exec_tree(node->left, TRUE, stks, tmp_fds);
		tmp_fds = (t_fds){fd_pipe[0], fds.out};
		exec_tree(node->right, TRUE, stks, tmp_fds);
	}
	close_pipes(stks->pipes);
	if (!from_pipe) //att car: cmd <-pipe-> et->pipeline (enum dc)(si parenthese)
		wait_all(stks->pids, pid);
	return (TRUE);
}
