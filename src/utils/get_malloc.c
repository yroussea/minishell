/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_malloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basverdi <basverdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 19:50:41 by yroussea          #+#    #+#             */
/*   Updated: 2024/07/09 09:16:14 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	close_heredoc(t_node *node)
{
	t_lst_redir	*redir;

	if (!node)
		return ;
	redir = node->redir;
	while (redir)
	{
		if (redir->type == HEREDOC)
			close(redir->heredoc_fd);
		redir = redir->next;
	}
	close_heredoc(node->left);
	close_heredoc(node->right);
}

t_node	*ft_get_root(t_node *node, t_bool reset, t_bool free_tree)
{
	static t_node	*root = NULL;

	if (reset)
		root = node;
	if (free_tree)
	{
		close_heredoc(root);
		ft_free_tree(root);
		root = NULL;
	}
	return (root);
}

t_bool	ft_get_lsts(t_lst_ope *ope, t_lst_com *com, t_bool reset, \
	t_bool free_lst)
{
	static t_lst_ope	*lst_operator = NULL;
	static t_lst_com	*lst_cmd = NULL;

	if (reset)
	{
		lst_operator = ope;
		lst_cmd = com;
	}
	if (free_lst)
	{
		ft_lst_com_free(lst_cmd);
		ft_lst_ope_free(lst_operator);
		ft_get_lsts(NULL, NULL, TRUE, FALSE);
	}
	return (TRUE);
}

t_data_stk	*ft_get_stks(t_data_stk *stks, t_bool reset, t_bool free_stks)
{
	static t_data_stk	*data_stks = NULL;

	if (reset)
		data_stks = stks;
	if (free_stks)
	{
		ft_stk_pipe_free(*data_stks->pipes);
		ft_stk_pid_free(*data_stks->pids);
		free(data_stks);
		data_stks = NULL;
	}
	return (data_stks);
}

t_bool	ft_get_envp(t_lst_envp *lst_envp, t_bool reset, t_bool free_envp)
{
	static t_lst_envp	*envp = NULL;

	if (reset)
		envp = lst_envp;
	if (free_envp)
	{
		free_lst_envp(envp);
		envp = NULL;
	}
	return (TRUE);
}
