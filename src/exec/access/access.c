/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basverdi <basverdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 16:45:31 by basverdi          #+#    #+#             */
/*   Updated: 2024/03/21 18:55:34 by basverdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*get_access(t_lst_envp *lst_envp, char *cmd)
{
	char	*paths;
	char	path;

	if (cmd && *cmd && access(cmd, F_OK) == 0)
		return (ft_strdup(cmd));
	paths = get_envp_variable(lst_envp, "PATH");
	path = ft_strdup("");
	while (paths && paths && path && access(path, F_OK))
	{
		free(path);
		path = ft_vjoin(3, "", *paths++, "/", cmd);
	}
	ft_magic_free("%1", paths);
	if (cmd)
		free(cmd);
	return (path);
}
