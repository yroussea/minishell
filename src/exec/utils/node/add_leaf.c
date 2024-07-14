/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_leaf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basverdi <basverdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 18:52:30 by yroussea          #+#    #+#             */
/*   Updated: 2024/07/14 17:35:43 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

t_bool	ft_open_redir(t_node *node, t_lst_com *cmd)
{
	t_lst_redir	*tmp;

	if (!cmd || !cmd->redir)
		return (ERROR);
	tmp = cmd->redir;
	while (tmp)
	{
		if (invalide_single_redir(tmp))
			return (FALSE);
		if (tmp->type == HEREDOC)
		{
			if (!ft_lst_redir_heredoc(&node->redir, HEREDOC, \
					ft_heredoc(tmp->file)))
				return (FALSE);
			node->redir->file = ft_strdup(tmp->file);
		}
		else
		{
			if (!ft_lst_redir_add(&node->redir, tmp->type, \
			ft_strdup(tmp->file)))
				return (FALSE);
		}
		tmp = tmp->next;
	}
	return (TRUE);
}

t_bool	add_single_leaf(t_node *root, t_node *leaf)
{
	if (!root)
		return (FALSE);
	if (!root->left)
		return (add_child(root, leaf, LEFT));
	if (root->left->type != CMD && add_single_leaf(root->left, leaf))
		return (TRUE);
	if (!root->right)
		return (add_child(root, leaf, RIGHT));
	if (root->right->type != CMD && add_single_leaf(root->right, leaf))
		return (TRUE);
	return (FALSE);
}

void	init_root(t_node **root, t_lst_com *cmd)
{
	*root = init_node(CMD);
	ft_get_root(*root, TRUE, FALSE);
	fill_node(*root, cmd);
}

t_bool	tree_add_leaf_on_tree(t_node **root, t_node *new_node, t_lst_com *cmd)
{
	if (!fill_node(new_node, cmd) || !add_single_leaf(*root, new_node))
	{
		ft_free_tree(new_node);
		ft_get_root(NULL, FALSE, TRUE);
		return (TRUE);
	}
	if (!ft_open_redir(new_node, cmd))
	{
		ft_get_root(NULL, FALSE, TRUE);
		return (TRUE);
	}
	return (FALSE);
}

t_bool	ft_add_all_leaf(t_node **root, t_lst_com *cmd, t_lst_envp **envp)
{
	t_node	*new_node;

	if (!root || !cmd)
		return (ERROR);
	if (!*root)
	{
		init_root(root, cmd);
		if (!ft_open_redir(*root, cmd))
		{
			ft_get_root(NULL, FALSE, TRUE);
			return (ERROR);
		}
		(*root)->envp = envp;
		cmd = cmd->next;
	}
	while (cmd)
	{
		new_node = init_node(CMD);
		if (tree_add_leaf_on_tree(root, new_node, cmd))
			return (ERROR);
		new_node->envp = envp;
		cmd = cmd->next;
	}
	return (TRUE);
}
