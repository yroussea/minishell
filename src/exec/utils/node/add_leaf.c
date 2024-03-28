/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_leaf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basverdi <basverdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 18:52:30 by yroussea          #+#    #+#             */
/*   Updated: 2024/03/27 20:12:57 by yroussea         ###   ########.fr       */
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
		if (tmp->type == HEREDOC)
		{
			if (!ft_lst_redir_heredoc(&node->redir, HEREDOC, \
					ft_heredoc(tmp->file)))
				return (FALSE);
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

t_bool	ft_add_all_leaf(t_node **root, t_lst_com *cmd, t_lst_envp **envp)
{
	t_node	*new_node;

	if (!root)
		return (ERROR);
	if (!*root)
	{
		*root = init_node(CMD);
		ft_get_root(*root, TRUE, FALSE);
		fill_node(*root, cmd);
		ft_open_redir(*root, cmd);
		(*root)->envp = envp;
		cmd = cmd->next;
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
		new_node->envp = envp;
		cmd = cmd->next;
	}
	return (TRUE);
}
