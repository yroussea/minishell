/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_and.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 16:56:19 by yroussea          #+#    #+#             */
/*   Updated: 2024/03/20 18:41:32 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_bool	exec_and(t_node *node, t_bool from_pipe, t_data_stk *stks, t_fds fds)
{
	/*(si dans pipe faire la suite dans un fork puis exit)
	 * dup2 entrer (si pas STDIN)
	 * exectree pour la gauche
	 * recup depuis la pile le pid
	 * close les pipes
	 * wait le fils
	 * si le fils a reussit (global ig)
	 * ->executer a droite
	 */
	(void)node;
	(void)stks;
	(void)fds;
	return (ERROR);
}
