/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 18:39:34 by yroussea          #+#    #+#             */
/*   Updated: 2024/03/16 19:12:43 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

t_node	*init_node(t_type_of_node type)
{
	t_node	*node;

	node = ft_calloc(1, sizeof(t_node));
	if (!node)
		return (NULL);
	node->cmd = NULL;
	node->args = NULL;
	node->left = NULL;
	node->right = NULL;
	node->infile = 0;
	node->outfile = 1;
	node->type = type;
	return (node);
}

t_bool	add_child(t_node *root, t_node *new_node, t_priority prio)
{
	if (prio == LEFT && root->left == NULL)
	{
		root->left = new_node;
		return (TRUE);
	}
	if (prio == RIGHT && root->right == NULL)
	{
		root->right = new_node;
		return (TRUE);
	}
	if (!root->right && !root->left)
		return (ERROR);
	return (FALSE);
}

void	ft_free_node(t_node *node)
{
	if (!node)
		return ;
	ft_magic_free("%1 %2", node->cmd, node->args);
	free(node);
}

void	ft_free_tree(t_node *root)
{
	if (!root)
		return ;
	ft_free_tree(root->left);
	ft_free_tree(root->right);
	ft_free_node(root);
}
