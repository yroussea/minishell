/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 18:39:34 by yroussea          #+#    #+#             */
/*   Updated: 2024/07/09 09:16:14 by yroussea         ###   ########.fr       */
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
	node->redir = NULL;
	node->infile = 0;
	node->outfile = 1;
	node->errorfile = 2;
	node->type = type;
	return (node);
}

t_bool	fill_node(t_node *node, t_lst_com *cmd)
{
	if (!node)
		return (FALSE);
	if (cmd)
	{
		node->cmd = cmd->cmd;
		node->args = cmd->args;
	}
	return (TRUE);
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
	ft_lst_redir_free(node->redir);
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
