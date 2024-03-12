/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lst_envp.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 16:27:36 by yroussea          #+#    #+#             */
/*   Updated: 2024/03/12 16:33:38 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	envp_lst_len(t_lst_envp *lst_envp)
{
	if (!lst_envp)
		return (0);
	return (1 + envp_lst_len(lst_envp->next));
}

char	**envp_to_char(t_lst_envp *lst_envp)
{
	char	**envp;
	int		i;

	i = 0;
	envp = ft_calloc(sizeof(char *), envp_lst_len(lst_envp) + 1);
	while (envp && lst_envp)
	{
		envp[i] = ft_vjoin(2, "=", lst_envp->key, lst_envp->value);
		lst_envp = lst_envp->next;
		i += 1;
	}
	return (envp);
}
