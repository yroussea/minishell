/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basverdi <basverdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:50:00 by yroussea          #+#    #+#             */
/*   Updated: 2024/03/20 18:07:32 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <sys/select.h>

t_bool	exec_tree(t_node *node, t_lst_envp *envp, t_data_stk *stks, t_fds fds)
{
	ft_print_tree(node);
	(void)envp;
	(void)stks;
	(void)fds;
	return (FALSE);
	if (node->type == PIPE)
		exec_pipe(node, envp, stks, fds);
	if (node->type == AND)
		exec_and(node, envp, stks, fds);
	if (node->type == OR)
		exec_or(node, envp, stks, fds);
	if (node->type == CMD)
		exec_cmd(node, envp, stks, fds);
	return (TRUE);
}
