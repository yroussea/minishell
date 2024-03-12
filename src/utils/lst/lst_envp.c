/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_envp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 19:44:14 by yroussea          #+#    #+#             */
/*   Updated: 2024/03/12 15:10:55 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_lst_envp	*init_node_envp(char *key, char *value)
{
	t_lst_envp	*new;

	new = ft_calloc(1, sizeof(t_lst_envp));
	if (!new)
		return (NULL);
	new->key = key;
	if (ft_strncmp(key, "SHLVL", 6) == 0)
	{
		new->value = ft_itoa(ft_atoi(value) + 1);
		free(value);
	}
	else
		new->value = value;
	new->next = NULL;
	return (new);
}

void	free_lst_envp(t_lst_envp *lst_envp)
{
	t_lst_envp	*tmp;

	while (lst_envp)
	{
		ft_magic_free("%1 %1", lst_envp->value, lst_envp->key);
		tmp = lst_envp;
		lst_envp = lst_envp->next;
		free(tmp);
	}
}

void	lst_envp_add_order(t_lst_envp **lst_envp, t_lst_envp *new, size_t len)
{
	if (!*lst_envp)
		*lst_envp = new;
	else if (ft_strncmp((*lst_envp)->key, new->key, len + 1) < 0)
		lst_envp_add_order(&(*lst_envp)->next, new, len);
	else
	{
		new->next = (*lst_envp);
		*lst_envp = new; 
	}
}

t_bool	lst_envp_add(t_lst_envp **lst_envp, char *variable)
{
	t_lst_envp	*tmp;
	char		**splited;

	if (!variable)
	{
		free_lst_envp(*lst_envp);
		return (ERROR);
	}
	splited = ft_split_first_sep(variable, '=');
	tmp = init_node_envp(splited[0], splited[1]);
	if (!tmp)
	{
		free_lst_envp(*lst_envp);
		ft_magic_free("%1 %2", variable, splited);
		free(variable);
		return (ERROR);
	}
	lst_envp_add_order(lst_envp, tmp, ft_strlen(tmp->key));
	ft_magic_free("%1 %1", variable, splited);
	return (TRUE);
}

t_lst_envp	*init_lst_envp(char **envp)
{
	t_lst_envp	*lst_envp;

	lst_envp = NULL;
	while (*envp)
	{
		if (lst_envp_add(&lst_envp, ft_strdup(*envp)) == ERROR)
			return (NULL);
		envp++;
	}
	return (lst_envp);
}
