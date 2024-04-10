/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_or.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basverdi <basverdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 16:56:25 by yroussea          #+#    #+#             */
/*   Updated: 2024/04/10 18:54:34 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_bool	exec_or(t_node *node, t_from_pipe from_pipe, t_data_stk *stks, t_fds fds)
{
	int	pid;
	/*(si dans pipe faire la suite dans un fork puis exit)
	 * dup2 entrer (si pas STDIN)
	 * exectree pour la gauche
	 * recup depuis la pile le pid
	 * close les pipes
	 * wait le fils
	 * si le fils a echouer (global ig)
	 * ->executer a droite
	 */
	if (fds.in != 0)
		ft_dup2(fds.in, STDIN_FILENO);
	if (fds.out != 1)
		ft_dup2(fds.out, STDOUT_FILENO);
	exec_tree(node->left, from_pipe, stks, fds);
	pid = stk_pid_pop(stks->pids);
	ft_close_pipe((stks)->pipes);
	waitpid(pid, NULL, 0);
	if (1) /*fils echoue*/
		exec_tree(node->right, from_pipe, stks, fds);
	(void)node;
	(void)fds;
	return (ERROR);
}
