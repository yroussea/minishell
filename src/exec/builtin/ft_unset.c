/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basverdi <basverdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 17:32:10 by basverdi          #+#    #+#             */
/*   Updated: 2024/04/18 12:31:53 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_unset(t_node *node, char *arg)
{
	int		i;
	char	*variable;

	(void)variable;
	i = ft_str_str_len(node->args);
	if (i == 1)
		ft_printf_fd(node->outfile, "unset: not enough arguments");
	else if (arg != NULL)
		remove_var_env(node->envp, arg);
	else
	{
		while (i--)
			remove_var_env(node->envp, node->args[i]);
	}
}
