/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basverdi <basverdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 18:01:15 by basverdi          #+#    #+#             */
/*   Updated: 2024/07/14 18:38:47 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <string.h>

int	count_space(char *str, int need_free)
{
	int		count;
	char	*tmp;

	count = 0;
	tmp = str;
	while (*str)
	{
		if (*str == ' ')
			count++;
		str++;
	}
	if (need_free)
		free(tmp);
	return (count);
}

char	*find_last_slash(char *start, char *end)
{
	while (end > start)
	{
		if (*end == '/')
			return (end);
		end -= 1;
	}
	return (start);
}

char	*find_dots(char *str)
{
	char	*tmp;
	size_t	len;

	len = ft_strlen(str);
	if (len == 0)
		return (NULL);
	if (str && ft_strncmp(str, "../", 3) == 0)
		return (str);
	tmp = ft_strnstr(str, "/../", len);
	if (tmp)
		return (tmp);
	return (ft_strnstr(str + len - 3, "/..", 3));
}

char	*get_absolut_path(char *relativ_path, char *pwd)
{
	char	*absolut_path;
	char	*dir;
	char	*dots;

	absolut_path = ft_vjoin(2, "/", pwd, relativ_path);
	while (1)
	{
		dots = find_dots(absolut_path);
		if (!dots)
			break ;
		if (dots != absolut_path)
			dir = find_last_slash(absolut_path, dots - 1);
		else
			dir = dots;
		ft_strlcpy(dir, dots + 3, ft_strlen(dots + 3) + 1);
	}
	return (absolut_path);
}

void	move_to_dir(char *path, t_node *node)
{
	static char	buf[4096];
	char		*tmp;
	int			error;

	error = 1;
	if (getcwd(buf, 4096))
	{
		tmp = get_absolut_path(path, buf);
		error = chdir(tmp);
		free(tmp);
	}
	if (error)
		error = chdir(path);
	if (!error)
	{
		if (get_new_pwd(node, 0))
			get_new_pwd(node, 1);
		return ;
	}
	cd_err(node, errno);
}
