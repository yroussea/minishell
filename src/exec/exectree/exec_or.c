/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_or.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 16:56:25 by yroussea          #+#    #+#             */
/*   Updated: 2024/03/20 18:20:17 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <sys/wait.h>
#include <unistd.h>

t_bool	exec_or(t_node *node, t_lst_envp *envp, t_data_stk *stks, t_fds fds)
{
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
	exec_tree(node->left, envp, stks, fds);
	int	pid;
	pid = stk_pid_pop(stks->pids);
	ft_close_pipe(*(stks)->pipes);
	waitpid(pid, NULL, 0);
	if (/*fils echoue*/ 1)
		exec_tree(node->right, envp, stks, fds);
	(void)node;
	(void)envp;
	(void)fds;
	return (ERROR);
}
