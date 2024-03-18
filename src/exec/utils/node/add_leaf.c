/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_leaf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basverdi <basverdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 18:52:30 by yroussea          #+#    #+#             */
/*   Updated: 2024/03/18 17:45:56 by basverdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

t_bool	ft_open_redir(t_node *node, t_lst_com *cmd)
{
	t_lst_redir	*tmp;

	if (!cmd || !cmd->redir || !cmd->redir->next)
		return (ERROR);
	tmp = cmd->redir->next->next;
	while (tmp)
	{
		if (tmp->type == DIRE_IN)
			if (!ft_lst_redir_add(&node->infile, tmp->type, \
			ft_strdup(tmp->file)))
				return (FALSE);
		if (tmp->type == ADD || tmp->type == DIRE_OUT || tmp->type == DIRE_TWO)
			if (!ft_lst_redir_add(&node->outfile, tmp->type, \
			ft_strdup(tmp->file)))
				return (FALSE);
		if (tmp->type == HEREDOC)
			if (!ft_lst_redir_add(&node->infile, DIRE_IN, \
			ft_heredoc(tmp->file)))
				return (FALSE);
		tmp = tmp->next;
	}
	return (TRUE);
}

t_bool	add_single_leaf(t_node *root, t_node *leaf)
{
	if (!root)
		return (ERROR);
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

t_bool	ft_add_all_leaf(t_node **root, t_lst_com *cmd)
{
	t_node	*new_node;

	if (!root)
		return (ERROR);
	if (!*root)
	{
		*root = init_node(CMD);
		return (fill_node(*root, cmd));
	}
	while (cmd)
	{
		new_node = init_node(CMD);
		if (!fill_node(new_node, cmd) || !add_single_leaf(*root, new_node))
		{
			ft_free_tree(new_node);
			return (ERROR);
		}
		if (!ft_open_redir(new_node, cmd))
			return (ERROR);
		cmd = cmd->next;
	}
	return (TRUE);
}
