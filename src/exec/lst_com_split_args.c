/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_com_split_args.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 12:32:29 by yroussea          #+#    #+#             */
/*   Updated: 2024/03/16 17:38:15 by yroussea         ###   ########.fr       */
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
	ft_lst_redir_add(&lst, DIRE_IN, ft_strdup("/dev/stdin"));
	ft_lst_redir_add(&lst, DIRE_OUT, ft_strdup("/dev/stdout"));
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
	if (!lst->args || !*lst->args)
		return (FALSE);
	lst->cmd = ft_strdup(*(lst->args));
	if (!lst->cmd || !lst->args || !*lst->args)
	{
		ft_magic_free("%1 %2", lst->cmd, lst->args);
		return (FALSE);
	}
	lst->redir = get_redir(s);
	if (!lst->redir)
	{
		ft_magic_free("%1 %2", lst->cmd, lst->args);
		return (FALSE);
	}
	return (TRUE);
}