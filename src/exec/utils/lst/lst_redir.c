/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 11:30:24 by yroussea          #+#    #+#             */
/*   Updated: 2024/07/09 09:16:14 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	lst_redir_add_back(t_lst_redir **lst, t_lst_redir *new)
{
	if (!*lst)
		*lst = new;
	else
		lst_redir_add_back(&(*lst)->next, new);
}

t_bool	ft_lst_redir_add(t_lst_redir **lst, t_type_of_node type, char *file)
{
	t_lst_redir	*tmp;

	tmp = init_node_redir(type, file);
	if (!tmp)
	{
		ft_lst_redir_free(*lst);
		free(file);
		return (FALSE);
	}
	lst_redir_add_back(lst, tmp);
	return (TRUE);
}

t_bool	ft_lst_redir_heredoc(t_lst_redir **lst, t_type_of_node type, int fd)
{
	t_lst_redir	*tmp;

	if (fd == -1)
		return (FALSE);
	tmp = init_node_redir(type, NULL);
	if (!tmp)
	{
		ft_lst_redir_free(*lst);
		return (FALSE);
	}
	tmp->heredoc_fd = fd;
	lst_redir_add_back(lst, tmp);
	return (TRUE);
}

void	ft_lst_redir_free(t_lst_redir *lst)
{
	t_lst_redir	*tmp;

	while (lst)
	{
		tmp = lst;
		free(lst->file);
		lst = lst->next;
		free(tmp);
	}
}

t_lst_redir	*init_node_redir(t_type_of_node type, char *file)
{
	t_lst_redir	*new;

	new = ft_calloc(1, sizeof(t_lst_redir));
	if (!new)
		return (NULL);
	new->type = type;
	new->file = file;
	new->next = NULL;
	return (new);
}
