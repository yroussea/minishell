/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_com_split_args.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basverdi <basverdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 12:32:29 by yroussea          #+#    #+#             */
/*   Updated: 2024/07/10 09:40:44 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_bool	is_redir(char *s)
{
	if (get_type(s) >= 4 && get_type(s) <= 8)
		return (TRUE);
	return (FALSE);
}

t_bool	init_skip(int *j, t_bool skip)
{
	*j += 1;
	return (skip);
}

static t_type_of_node	init_chose(int *j, t_type_of_node chose)
{
	*j += 1;
	return (chose);
}

static t_lst_redir	*get_redir(char **s, int i, int j)
{
	t_lst_redir		*lst;
	t_type_of_node	chose;

	chose = 0;
	lst = NULL;
	while (s && *(s + i + j))
	{
		if (ft_strncmp(*(s + i + j), " ", 2) == 0)
			j += 1;
		else if (chose)
		{
			if (!ft_lst_redir_add(&lst, chose, ft_strdup(*(s + i + j))))
				lst = NULL;
			chose = init_chose(&j, 0);
		}
		else if (is_redir(*(s + i + j)))
			chose = init_chose(&j, get_type(*(s + i + j)));
		else
			i += 1;
	}
	if (chose && !ft_lst_redir_add(&lst, chose, NULL))
		lst = NULL;
	return (lst);
}

t_bool	split_args(char **s, t_lst_com *lst)
{
	lst->cmd = NULL;
	lst->args = NULL;
	lst->redir = NULL;
	if (!s)
		return (FALSE);
	lst->args = ft_duptab(s, 0, 0);
	lst->redir = get_redir(s, 0, 0);
	if ((!lst->args || !*lst->args) && (!lst->redir))
	{
		ft_magic_free("%2", lst->args);
		return (FALSE);
	}
	return (TRUE);
}
