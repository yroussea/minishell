/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_or.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basverdi <basverdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 16:56:25 by yroussea          #+#    #+#             */
/*   Updated: 2024/06/17 18:16:43 by basverdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_bool	exec_or(t_node *node, t_from_pipe from_pipe, t_data_stk *stks, t_fds \
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
			get_set_exit_code(130, TRUE);
		else
			get_set_exit_code(WEXITSTATUS(tmp_err), TRUE);
	}
	if (get_set_exit_code(0, FALSE))
		exec_tree(node->right, from_pipe, stks, fds);
	return (TRUE);
}
