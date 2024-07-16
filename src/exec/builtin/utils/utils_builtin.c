/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basverdi <basverdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 15:55:27 by basverdi          #+#    #+#             */
/*   Updated: 2024/07/16 13:20:54 by yroussea         ###   ########.fr       */
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

void	check_active(int *active, int *active_old)
{
	if (*active_old == 1 && *active == 1)
		*active = 1;
	else if (*active == -1 || *active_old == 1)
		*active = -1;
	else
		*active = 0;
}
