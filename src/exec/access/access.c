/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basverdi <basverdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 16:45:31 by basverdi          #+#    #+#             */
/*   Updated: 2024/03/26 16:32:43 by basverdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <unistd.h>

extern int g_exitcode;

char	*get_access(t_lst_envp *lst_envp, char *cmd)
{
	char	*path;
	char	**allpaths;
	int		i;

	if (!cmd)
		return (NULL);
	if (cmd && *cmd && access(cmd, X_OK) == 0)
		return (cmd);
	allpaths = get_all_path(lst_envp);
	i = 0;
	while (allpaths && allpaths[i])
	{
		path = ft_vjoin(2, "/", allpaths[i], cmd);
		if (path && *path && access(path, X_OK) == 0)
		{
			ft_magic_free("%2", allpaths);
			return (path);
		}
		free(path);
		i += 1;
	}
	ft_magic_free("%2", allpaths);
	g_exitcode = 127;
	return (NULL);
}
