/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basverdi <basverdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 18:00:07 by basverdi          #+#    #+#             */
/*   Updated: 2024/04/18 16:24:26 by basverdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_env(t_node *node, char *str)
{
	t_lst_envp	*envp;
	char		*vars;

	envp = *(node->envp);
	if (ft_str_str_len(node->args) > 1)
	{
		ft_printf_fd(node->outfile, "env: %s: No such file or directory\n", node->args[1]);
		return ;
	}
	while (envp)
	{
		if (str)
		{
			if (!envp->value)
				vars = ft_vjoin(2, "", str, envp->key);
			else
				vars = ft_vjoin(5, "", str, envp->key, "=\"", envp->value, "\"");
		}
		else
			vars = ft_vjoin(4, "", str, envp->key, "=", envp->value);
		ft_printf_fd(node->outfile, "%s\n", vars);
		free(vars);
		envp = envp->next;
	}
}
