/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   better_fnct_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basverdi <basverdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 16:10:51 by basverdi          #+#    #+#             */
/*   Updated: 2024/05/01 16:32:13 by basverdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	remove_var_env(t_lst_envp **lst_envp, char *variable)
{
	char		**splited;
	t_lst_envp	*tmp;
	t_lst_envp	*checkpoint;

	if (!*lst_envp)
		return ;
	splited = ft_split_first_sep(variable, '=');
	if (ft_strncmp((*lst_envp)->key, *splited, ft_strlen(*splited)) == 0)
	{
		tmp = *lst_envp;
		*lst_envp = (*lst_envp)->next;
		ft_free_split(splited);
		ft_magic_free("%1 %1 %1", tmp->key, tmp->value, tmp);
		return ;
	}
	checkpoint = index_removed_var(*lst_envp, *splited);
	ft_free_split(splited);
	if (checkpoint == NULL)
		return ;
	tmp = *lst_envp;
	while (tmp->next != checkpoint)
		tmp = tmp->next;
	tmp->next = tmp->next->next;
	ft_magic_free("%1 %1 %1", checkpoint->key, checkpoint->value, checkpoint);
}

char	**ft_duptab(char **s, int i, int j)
{
	char	**result;
	t_bool	skip;

	skip = FALSE;
	result = ft_calloc(ft_str_str_len(s), sizeof(char *));
	while (result && s && *(s + i + j))
	{
		if (ft_strncmp(*(s + i + j), " ", 2) == 0)
			j += 1;
		else if (skip)
			skip = init_skip(&j, FALSE);
		else if (is_redir(*(s + i + j)))
			skip = init_skip(&j, TRUE);
		else
		{
			result[i] = ft_strdup(s[i + j]);
			if (!result[i++])
			{
				ft_magic_free("%2", result);
				return (NULL);
			}
		}
	}
	return (result);
}
