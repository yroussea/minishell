/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lst_envp.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basverdi <basverdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 16:27:36 by yroussea          #+#    #+#             */
/*   Updated: 2024/07/17 13:20:24 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	get_os(t_lst_envp *lst_envp)
{
	while (lst_envp)
	{
		if (ft_strnstr(lst_envp->value, "ubuntu", ft_strlen(lst_envp->value)))
			return (1);
		if (ft_strnstr(lst_envp->value, "Apple", ft_strlen(lst_envp->value)))
			return (2);
		lst_envp = lst_envp->next;
	}
	return (0);
}

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
		if (!envp[i])
		{
			ft_magic_free("%2", envp);
			return (NULL);
		}
		lst_envp = lst_envp->next;
		i += 1;
	}
	return (envp);
}

char	*get_envp_variable(t_lst_envp *lst_envp, char *variable, int exist)
{
	static char	buf[4096];

	while (lst_envp && exist != -2)
	{
		if (exist <= lst_envp->active && variable && lst_envp->key && \
			ft_strncmp(lst_envp->key, variable, ft_strlen(variable) + 1) == 0)
			return (ft_strdup(lst_envp->value));
		lst_envp = lst_envp->next;
	}
	if (exist == -2 && variable && ft_strncmp(variable, "PWD", 3) == 0)
	{
		getcwd(buf, 4096);
		return (ft_strdup(buf));
	}
	if (variable && ft_strncmp(variable, "?", 1) == 0)
		return (ft_itoa(get_set_exit_code(0, FALSE)));
	return (NULL);
}

char	**get_all_path(t_lst_envp *lst_envp)
{
	while (lst_envp)
	{
		if (ft_strncmp(lst_envp->key, "PATH", 5) == 0)
			return (ft_split(lst_envp->value, ':'));
		lst_envp = lst_envp->next;
	}
	return (ft_split(".", ':'));
}
