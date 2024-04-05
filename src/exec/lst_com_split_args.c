/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_com_split_args.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basverdi <basverdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 12:32:29 by yroussea          #+#    #+#             */
/*   Updated: 2024/04/01 10:55:05 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_bool	is_redir(char *s)
{
	if (get_type(s) >= 4 && get_type(s) <= 8)
		return (TRUE);
	return (FALSE);
}

static char	**ft_duptab(char **s)
{
	char	**result;
	int		i;
	int		j;
	t_bool	skip;

	i = 0;
	j = 0;
	skip = FALSE;
	result = ft_calloc(ft_str_str_len(s), sizeof(char *));
	while (result && s && *(s + i + j))
	{
		if (ft_strncmp(*(s + i + j), " ", 2) == 0)
			j += 1;
		else if (skip)
		{
			j += 1;
			skip = FALSE;
		}
		else if (is_redir(*(s + i + j)))
		{
			j += 1;
			skip = TRUE;
		}
		else
		{
			result[i] = ft_strdup(s[i + j]);
			if (!result[i])
			{
				ft_magic_free("%2", result);
				return (NULL);
			}
			i += 1;
		}
	}
	return (result);
}

static t_lst_redir	*get_redir(char **s)
{
	t_lst_redir		*lst;
	int				i;
	int				j;
	t_type_of_node	chose;

	i = 0;
	j = 0;
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
			j += 1;
			chose = 0;
		}
		else if (is_redir(*(s + i + j)))
		{
			chose = get_type(*(s + i + j));
			j += 1;
		}
		else
			i += 1;
	}
	return (lst);
}

t_bool	split_args(char **s, t_lst_com *lst)
{
	lst->cmd = NULL;
	lst->args = NULL;
	lst->redir = NULL;
	if (!s)
		return (FALSE);
	lst->args = ft_duptab(s);
	lst->redir = get_redir(s);
	if ((!lst->args || !*lst->args) && (!lst->redir))
	{
		ft_magic_free("%2", lst->args);
		return (FALSE);
	}
	return (TRUE);
}
