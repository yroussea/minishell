/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   better_fnct_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basverdi <basverdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 16:10:51 by basverdi          #+#    #+#             */
/*   Updated: 2024/04/29 16:11:07 by basverdi         ###   ########.fr       */
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
