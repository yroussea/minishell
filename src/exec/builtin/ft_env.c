/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basverdi <basverdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 18:00:07 by basverdi          #+#    #+#             */
/*   Updated: 2024/03/25 18:07:32 by basverdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_env(t_node *node)
{
	t_lst_envp	*envp;

	envp = *(node->envp);
	while (envp)
	{
		ft_printf_fd(node->outfile, "%s=%s\n", envp->key, envp->value);
		envp = envp->next;
	}
}
