/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basverdi <basverdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 17:32:10 by basverdi          #+#    #+#             */
/*   Updated: 2024/04/29 16:02:50 by basverdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

extern int	g_exitcode;

static char	*get_variable(t_lst_envp *lst_envp, char *variable)
{
	while (lst_envp)
	{
		if (ft_strncmp(lst_envp->key, variable, ft_strlen(variable) + 1) == 0)
			return (ft_strdup(lst_envp->value));
		lst_envp = lst_envp->next;
	}
	return (NULL);
}

void	ft_unset(t_node *node, char *arg)
{
	int		i;
	char	*tmp;

	(void)arg;
	i = ft_str_str_len(node->args);
	if (arg != NULL)
	{
		tmp = get_variable(*node->envp, arg);
		if (tmp)
			remove_var_env(node->envp, arg);
		free(tmp);
	}
	else
	{
		i--;
		while (i > 0)
		{
			remove_var_env(node->envp, node->args[i]);
			i--;
		}
	}
}
