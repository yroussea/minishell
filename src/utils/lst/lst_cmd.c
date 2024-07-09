/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 18:06:16 by yroussea          #+#    #+#             */
/*   Updated: 2024/07/09 09:16:14 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	lst_cmd_add_back(t_lst_cmd **lst, t_lst_cmd *new)
{
	if (!*lst)
		*lst = new;
	else
		lst_cmd_add_back(&(*lst)->next, new);
}

t_bool	ft_lst_cmd_add(t_lst_cmd **lst, char **s, t_type_of_node type)
{
	t_lst_cmd	*tmp;

	if (!s || !*s)
	{
		ft_free_split(s);
		ft_lst_cmd_free(*lst);
		return (FALSE);
	}
	tmp = init_node_cmd(s, type);
	if (!tmp)
	{
		ft_lst_cmd_free(*lst);
		return (FALSE);
	}
	lst_cmd_add_back(lst, tmp);
	return (TRUE);
}

void	ft_lst_cmd_free(t_lst_cmd *lst)
{
	t_lst_cmd	*tmp;

	while (lst)
	{
		tmp = lst;
		ft_free_split(lst->cmd);
		lst = lst->next;
		free(tmp);
	}
}

t_lst_cmd	*init_node_cmd(char **s, t_type_of_node type)
{
	t_lst_cmd	*new;

	new = ft_calloc(1, sizeof(t_lst_cmd));
	if (!new)
		return (NULL);
	new->type = type;
	new->cmd = s;
	new->next = NULL;
	return (new);
}
