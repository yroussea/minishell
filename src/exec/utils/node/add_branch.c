/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_branch.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basverdi <basverdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 18:52:17 by yroussea          #+#    #+#             */
/*   Updated: 2024/07/09 09:16:14 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

t_bool	add_single_branch(t_node **root, t_node *new_node)
{
	if ((((*root)->type == AND || (*root)->type == OR) \
		&& new_node->type == PIPE))
	{
		if (add_child(*root, new_node, RIGHT))
			return (TRUE);
		return (add_single_branch(&(*root)->right, new_node));
	}
	else
	{
		if (!add_child(new_node, *root, LEFT))
			return (ERROR);
		*root = new_node;
	}
	return (TRUE);
}

static t_bool	annex_add_branch(t_node **root, t_type_of_node type)
{
	t_node		*new_node;

	if (!root)
		return (ERROR);
	new_node = init_node(type);
	if (!new_node)
		return (ERROR);
	if (!*root)
	{
		*root = new_node;
		return (TRUE);
	}
	return (add_single_branch(root, new_node));
}

t_bool	ft_add_all_branch(t_node **node, t_lst_ope *ope)
{
	while (ope)
	{
		if (!annex_add_branch(node, ope->type))
			return (ERROR);
		ope = ope->next;
	}
	ft_get_root(*node, TRUE, FALSE);
	return (TRUE);
}
