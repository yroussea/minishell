/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_com.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basverdi <basverdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 11:15:55 by yroussea          #+#    #+#             */
/*   Updated: 2024/07/14 17:36:09 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

t_lst_com	*lst_com_pop(t_lst_com **lst)
{
	if (!*lst)
		return (NULL);
	if (!(*lst)->next)
		return (*lst);
	return (lst_com_pop(&(*lst)->next));
}

void	lst_com_add_back(t_lst_com **lst, t_lst_com *new)
{
	if (!*lst)
		*lst = new;
	else
		lst_com_add_back(&(*lst)->next, new);
}

t_bool	ft_lst_com_add(t_lst_com **lst, char **s)
{
	t_lst_com	*tmp;

	if (!s || !*s)
	{
		ft_free_split(s);
		ft_lst_com_free(*lst);
		*lst = NULL;
		return (FALSE);
	}
	tmp = init_node_com(s);
	if (!tmp)
	{
		ft_lst_com_free(*lst);
		return (FALSE);
	}
	lst_com_add_back(lst, tmp);
	return (TRUE);
}

void	ft_lst_com_free(t_lst_com *lst)
{
	t_lst_com	*tmp;

	while (lst)
	{
		tmp = lst;
		ft_magic_free("%1 %2", lst->cmd, lst->args);
		ft_lst_redir_free(lst->redir);
		lst = lst->next;
		free(tmp);
	}
}

t_lst_com	*init_node_com(char **s)
{
	t_lst_com	*new;

	new = ft_calloc(1, sizeof(t_lst_com));
	if (!new)
		return (NULL);
	if (!split_args(s, new))
	{
		ft_magic_free("%1", new);
		return (NULL);
	}
	new->next = NULL;
	return (new);
}
