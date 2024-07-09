/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_ope.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 11:25:58 by yroussea          #+#    #+#             */
/*   Updated: 2024/07/09 09:16:14 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	lst_ope_add_back(t_lst_ope **lst, t_lst_ope *new)
{
	if (!*lst)
		*lst = new;
	else
		lst_ope_add_back(&(*lst)->next, new);
}

t_bool	ft_lst_ope_add(t_lst_ope **lst, t_type_of_node type)
{
	t_lst_ope	*tmp;

	tmp = init_node_ope(type);
	if (!tmp)
	{
		ft_lst_ope_free(*lst);
		return (FALSE);
	}
	lst_ope_add_back(lst, tmp);
	return (TRUE);
}

void	ft_lst_ope_free(t_lst_ope *lst)
{
	t_lst_ope	*tmp;

	while (lst)
	{
		tmp = lst;
		lst = lst->next;
		free(tmp);
	}
}

t_lst_ope	*init_node_ope(t_type_of_node type)
{
	t_lst_ope	*new;

	new = ft_calloc(1, sizeof(t_lst_ope));
	if (!new)
		return (NULL);
	new->type = type;
	new->next = NULL;
	return (new);
}
