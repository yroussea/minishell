/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:50:00 by yroussea          #+#    #+#             */
/*   Updated: 2024/03/18 16:24:53 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_bool	exec_pipe(t_node *node, t_lst_envp *envp)
{
	(void)node;
	(void)envp;
	return (ERROR);
}

t_bool	exec_and(t_node *node, t_lst_envp *envp)
{
	(void)node;
	(void)envp;
	return (ERROR);
}

t_bool	exec_or(t_node *node, t_lst_envp *envp)
{
	(void)node;
	(void)envp;
	return (ERROR);
}

t_bool	exec_cmd(t_node *node, t_lst_envp *envp)
{
	(void)node;
	(void)envp;
	return (ERROR);
}

t_bool	exec_tree(t_node *node, t_lst_envp *envp)
{
	ft_print_tree(node);
	if (node->type == PIPE)
		exec_pipe(node, envp);
	if (node->type == AND)
		exec_and(node, envp);
	if (node->type == OR)
		exec_or(node, envp);
	if (node->type == CMD)
		exec_cmd(node, envp);
	return (FALSE);
}
