/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basverdi <basverdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 16:45:31 by basverdi          #+#    #+#             */
/*   Updated: 2024/04/12 13:50:01 by basverdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

extern int	g_exitcode;

void	error_access(char *cmd)
{
	if (*cmd == '/')
		ft_printf_fd(2, "petit-coquillage: %s: No such file or directory\n", \
			cmd);
	else
		ft_printf_fd(2, "%s: command not found\n", cmd);
}

char	*get_access(t_lst_envp *lst_envp, char *cmd)
{
	char	*path;
	char	**allpaths;
	int		i;

	if (!cmd)
		return (NULL);
	if (cmd && *cmd && access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
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
	error_access(cmd);
	return (NULL);
}
