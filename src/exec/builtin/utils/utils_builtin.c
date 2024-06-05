/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basverdi <basverdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 15:55:27 by basverdi          #+#    #+#             */
/*   Updated: 2024/06/05 16:57:08 by basverdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	display_env(t_node *node)
{
	ft_env(node, "declare -x ", 1);
}

char	*is_envp_variable(t_lst_envp *lst_envp, char *variable)
{
	while (lst_envp)
	{
		if (ft_strncmp(lst_envp->key, variable, ft_strlen(variable) + 1) == 0)
			return (ft_strdup(lst_envp->key));
		lst_envp = lst_envp->next;
	}
	return (NULL);
}
