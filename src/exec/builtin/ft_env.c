/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basverdi <basverdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 18:00:07 by basverdi          #+#    #+#             */
/*   Updated: 2024/07/16 13:23:00 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_bool	env_err(t_node *node)
{
	if (ft_str_str_len(node->args) > 1)
	{
		ft_printf_fd(node->outfile, "env: %s: No such file or directory\n", \
			node->args[1]);
		return (TRUE);
	}
	return (FALSE);
}

void	ft_env(t_node *node, char *str, int type)
{
	t_lst_envp	*envp;
	char		*vars;

	envp = *(node->envp);
	if (env_err(node))
		return ;
	while (envp)
	{
		if (str)
		{
			if (!envp->value)
				vars = ft_vjoin(2, "", str, envp->key);
			else
				vars = ft_vjoin(5, "", str, envp->key, "=\"", envp->value, \
					"\"");
		}
		else
			vars = ft_vjoin(4, "", str, envp->key, "=", envp->value);
		if ((envp->value || type == 1) && envp->active == 1)
			ft_printf_fd(node->outfile, "%s\n", vars);
		envp = envp->next;
		free(vars);
	}
}
