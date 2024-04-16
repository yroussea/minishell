/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basverdi <basverdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:53:22 by basverdi          #+#    #+#             */
/*   Updated: 2024/04/16 18:12:06 by basverdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_export(t_node *node, char *arg)
{
	int		i;
	char	**variable;

	i = ft_str_str_len(node->args);
	if (!i && !arg && !*arg)
		ft_env(node);
	else if (arg != NULL)
	{
		variable = ft_split_first_sep(arg, '=');
		if (get_envp_variable(*node->envp, variable[0]))
			ft_unset(node, variable[0]);
		lst_envp_add(node->envp, arg);
	}
	else
	{
		while (i--)
		{
			variable = ft_split_first_sep(node->args[i], '=');
			if (get_envp_variable(*node->envp, variable[0]))
				ft_unset(node, variable[0]);
			lst_envp_add(node->envp, node->args[i]);
		}
	}
}
