/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basverdi <basverdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:50:00 by yroussea          #+#    #+#             */
/*   Updated: 2024/03/22 15:49:10 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <sys/select.h>
#include <unistd.h>

t_bool	exec_tree(t_node *node, t_bool from_pipe, t_data_stk *stks, t_fds fds)
{
	ft_print_tree(node);
//	(void)stks;
//	(void)fds;
//	return (FALSE);
	if (node->type == PIPE)
		exec_pipe(node, from_pipe, stks, fds);
	if (node->type == AND)
		exec_and(node, from_pipe, stks, fds);
	if (node->type == OR)
		exec_or(node, from_pipe, stks, fds);
	if (node->type == CMD)
		exec_cmd(node, from_pipe, stks, fds);
	return (TRUE);
}
