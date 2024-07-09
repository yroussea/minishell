/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basverdi <basverdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 16:57:05 by yroussea          #+#    #+#             */
/*   Updated: 2024/07/09 09:16:14 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	wait_all(t_stack_id **stk, int checkpoint)
{
	int		pid;
	int		tmp_code;
	t_bool	last_cmd;

	last_cmd = TRUE;
	while (stk && *stk)
	{
		pid = stk_pid_pop(stk);
		if (pid == -1 || pid == checkpoint)
			break ;
		waitpid(pid, &tmp_code, 0);
		if (last_cmd)
		{
			get_set_exit_code(WEXITSTATUS(tmp_code), TRUE);
			check_status(tmp_code);
			last_cmd = FALSE;
		}
	}
}

t_bool	exec_pipe_under_pipe(t_node *node, t_data_stk *stks, t_fds fds)
{
	int				fd_pipe[2];
	int				fd_pipe_return[2];
	t_fds			tmp_fds;

	if (ft_pipe(fd_pipe) < 0)
		return (FALSE);
	ft_stk_pipe_add(stks->pipes, fd_pipe);
	tmp_fds = (t_fds){fds.in, fd_pipe[1]};
	exec_tree(node->left, LEFT_PIPE, stks, tmp_fds);
	if (ft_pipe(fd_pipe_return) < 0)
		return (FALSE);
	tmp_fds = (t_fds){fd_pipe[0], fd_pipe_return[1]};
	ft_stk_pipe_add(stks->pipes, fd_pipe_return);
	exec_tree(node->right, RIGHT_PIPE, stks, tmp_fds);
	free(stk_pipe_pop(stks->pipes));
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
	ft_stk_pipe_add(stks->pipes, fd_pipe_return);
	ft_stk_pipe_add(stks->pipes, fd_pipe);
	exec_tree(node->right, RIGHT_PIPE, stks, tmp_fds);
	free(stk_pipe_pop(stks->pipes));
	free(stk_pipe_pop(stks->pipes));
	ft_close(2, fd_pipe[0], fd_pipe[1]);
	ft_stk_pipe_add(stks->pipes, fd_pipe_return);
	return (TRUE);
}

t_bool	exec_pipe_top(t_node *node, t_data_stk *stks, t_fds fds)
{
	int				fd_pipe[2];
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
	tmp_fds = (t_fds){fd_pipe[0], fds.out};
	ft_stk_pipe_add(stks->pipes, fd_pipe);
	exec_tree(node->right, RIGHT_PIPE, stks, tmp_fds);
	close_pipes(stks->pipes);
	return (TRUE);
}

t_bool	exec_pipe(t_node *node, t_from_pipe from_pipe, t_data_stk *stks, t_fds \
	fds)
{
	int			fd_pipe[2];
	int			pid;
	t_stack_id	*tmp;

	tmp = *stks->pids;
	if (tmp)
		pid = tmp->pid;
	else
		pid = -1;
	if (node->left->type == PIPE)
		exec_pipe_top(node, stks, fds);
	else
	{
		if (ft_pipe(fd_pipe) < 0)
			return (ERROR);
		ft_stk_pipe_add(stks->pipes, fd_pipe);
		exec_tree(node->left, LEFT_PIPE, stks, (t_fds){fds.in, fd_pipe[1]});
		exec_tree(node->right, RIGHT_PIPE, stks, (t_fds){fd_pipe[0], fds.out});
		close_pipes(stks->pipes);
	}
	if (from_pipe == NO_PIPE)
		wait_all(stks->pids, pid);
	return (TRUE);
}
