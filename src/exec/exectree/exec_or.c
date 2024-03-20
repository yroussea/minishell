/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_or.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 16:56:25 by yroussea          #+#    #+#             */
/*   Updated: 2024/03/20 17:00:00 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_bool	exec_or(t_node *node, t_lst_envp *envp, t_stack_id *stk_pid, t_fds fds)
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
	(void)node;
	(void)envp;
	(void)stk_pid;
	(void)fds;
	return (ERROR);
}
