/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 16:57:05 by yroussea          #+#    #+#             */
/*   Updated: 2024/03/20 18:03:37 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_bool	exec_pipe(t_node *node, t_lst_envp *envp, t_data_stk *stks, t_fds fds)
{
	int		fd_pipe[2];

	if (ft_pipe(fd_pipe) < 0)
		return (ERROR);
	ft_stk_pipe_add(stks->pipes, fd_pipe);
	fds.in = 0;
	fds.out = fd_pipe[1];
	exec_tree(node->left, envp, stks, fds);
	fds.in = fd_pipe[0];
	fds.out = 1;
	exec_tree(node->right, envp, stks, fds);
	//wait la pipeline?
	if (ft_close(2, fd_pipe[0], fd_pipe[1]) < 0)
		return (ERROR);
	return (TRUE);
}
