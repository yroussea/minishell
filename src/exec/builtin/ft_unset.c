/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basverdi <basverdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 17:32:10 by basverdi          #+#    #+#             */
/*   Updated: 2024/07/09 12:04:18 by yroussea         ###   ########.fr       */
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
		if (node->args[0] && node->args[1] && node->args[1][0] == '-')
			get_set_exit_code(2, TRUE);
		i--;
		while (i > 0)
		{
			remove_var_env(node->envp, node->args[i]);
			i--;
		}
	}
}
