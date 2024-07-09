/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basverdi <basverdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 17:32:10 by basverdi          #+#    #+#             */
/*   Updated: 2024/07/09 09:16:14 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_unset(t_node *node, char *arg)
{
	int		i;
	char	*tmp;

	i = ft_str_str_len(node->args);
	if (arg)
	{
		tmp = is_envp_variable(*node->envp, arg);
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
