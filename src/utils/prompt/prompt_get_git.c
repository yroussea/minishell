/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_get_git.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basverdi <basverdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 11:36:21 by yroussea          #+#    #+#             */
/*   Updated: 2024/07/09 09:16:14 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*smaller_pwd(char *pwd)
{
	char	*res;
	char	*rchr;

	res = ft_strdup(pwd);
	if (!res)
		return (NULL);
	rchr = ft_strrchr(res, '/');
	if (!rchr || !res)
	{
		free(res);
		return (NULL);
	}
	*rchr = 0;
	return (res);
}

void	get_branch(char **branch, char *config_file)
{
	char	*line;
	int		fd;
	char	*tmp;

	fd = open(config_file, 0);
	line = get_next_line(fd);
	while (line)
	{
		if (!*branch && ft_strnstr(line, "branch", ft_strlen(line)))
		{
			tmp = ft_strchr(line, '"');
			if (!tmp)
				tmp = line;
			*branch = ft_vjoin(6, "", CYAN, "git:(", RED, BRANCH, " ", \
				tmp + 1);
			if (*branch && tmp != line)
				*ft_strrchr(*branch, '"') = 0;
		}
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
}

t_bool	is_git_file(char *pwd, char **branch)
{
	char	*join;
	int		access_git;
	char	*smal_pwd;

	if (!pwd)
		return (FALSE);
	join = ft_vjoin(2, "/", pwd, ".git/config");
	access_git = access(join, R_OK) + 1;
	if (access_git == TRUE)
	{
		get_branch(branch, join);
		free(join);
		return (TRUE);
	}
	free(join);
	smal_pwd = smaller_pwd(pwd);
	access_git = is_git_file(smal_pwd, branch);
	free(smal_pwd);
	return (access_git);
}
