/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_envp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 19:44:14 by yroussea          #+#    #+#             */
/*   Updated: 2024/03/11 20:42:51 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_lst_envp	*init_node_envp(char *variable)
{
	t_lst_envp	*new;

	new = ft_calloc(1, sizeof(t_lst_envp));
	if (!new)
		return (NULL);
	new->variable = variable;
	new->next = NULL;
	return (new);
}

void	free_lst_envp(t_lst_envp *lst_envp)
{
	t_lst_envp	*tmp;

	while (lst_envp)
	{
		free(lst_envp->variable);
		tmp = lst_envp;
		lst_envp = lst_envp->next;
		free(tmp);
	}
}

void	lst_envp_add_order(t_lst_envp **lst_envp, t_lst_envp *new, size_t len)
{
	if (!*lst_envp)
		*lst_envp = new;
	else if (ft_strncmp((*lst_envp)->variable, new->variable, len + 1) < 0)
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

	if (!variable)
	{
		free_lst_envp(*lst_envp);
		return (ERROR);
	}
	tmp = init_node_envp(variable);
	if (!tmp)
	{
		free_lst_envp(*lst_envp);
		free(variable);
		return (ERROR);
	}
	lst_envp_add_order(lst_envp, tmp, ft_strlen(tmp->variable));
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
