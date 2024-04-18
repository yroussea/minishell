/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basverdi <basverdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:53:22 by basverdi          #+#    #+#             */
/*   Updated: 2024/04/18 13:00:22 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	display_env(t_node *node)
{
	ft_env(node);
}

void	create_env(t_node *node, char *arg)
{
	char	**variable;
	char	*tmp;

	variable = ft_split_first_sep(arg, '=');
	tmp = get_envp_variable(*node->envp, variable[0]);
	if (tmp)
		ft_unset(node, variable[0]);
	free(tmp);
	ft_free_split(variable);
	lst_envp_add(node->envp, ft_strdup(arg));
}

void	ft_export(t_node *node, char *arg)
{
	int		i;
	int		n;

	i = ft_str_str_len(node->args);
	if (i == 1)
	{
		display_env(node);
		return ;
	}
	if (arg)
	{
		create_env(node, arg);
		return ;
	}
	n = 1;
	while (n < i)
	{
		create_env(node, node->args[n]);
		display_env(node);
		n += 1;
	}
}
