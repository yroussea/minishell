/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basverdi <basverdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 16:45:31 by basverdi          #+#    #+#             */
/*   Updated: 2024/04/16 18:02:42 by basverdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <sys/stat.h>

extern int	g_exitcode;

void	print_error_access(t_error error_type, char *cmd)
{
	if (error_type == NOT_CMD && cmd && *cmd == '/')
		ft_printf_fd(2, NO_FILE, cmd);
	else if (error_type == NOT_CMD)
		ft_printf_fd(2, CMD_NOT_FOUND, cmd);
	//il va en falloir bc
}

t_bool	access_errors(struct stat st, int status, char *path, char *cmd)
{
	if (path && *path)
		status = stat(path, &st);
	else
	{
		if (cmd)
			print_error_access(NOT_CMD, cmd);
		if (cmd)
			g_exitcode = 127;
		return (TRUE);
	}
	if (S_ISDIR(st.st_mode))
		print_error_access(IS_DIR, path);
	if (S_ISDIR(st.st_mode))
		return (TRUE);
	else if (status != -1 && path && *path && access(path, X_OK))
		print_error_access(NO_PERM, cmd);
	else if (status == -1 && errno == ENOTDIR)
		print_error_access(ISNOT_DIR, cmd);
	else if (status == -1 && errno == ENOENT)
	{
		print_error_access(NOT_CMD, cmd);
		g_exitcode = 127;
		return (TRUE);
	}
	else if (S_ISFIFO(st.st_mode))
		print_error_access(NO_PERM, cmd);
	else
		return (FALSE);
	g_exitcode = 126;
	return (TRUE);
}

char	*extract_path(t_lst_envp *lst_envp, char *cmd)
{
	char		*path;
	char		**allpaths;
	int			i;

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
			{
				ft_magic_free("%2", allpaths);
				return (path);
			}
		}
		free(path);
		i += 1;
	}
	ft_magic_free("%2", allpaths);
	return (NULL);
}

char	*get_access(t_lst_envp *lst_envp, char *cmd)
{
	struct stat	st;
	int			status;
	char		*path;

	status = 0;
	st.st_mode = 0;
	path = extract_path(lst_envp, cmd);
	if (access_errors(st, status, path, cmd) == FALSE)
		return (path);
	free(path);
	return (NULL);
}
