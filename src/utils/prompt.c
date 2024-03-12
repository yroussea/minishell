/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastienverdier-vaissiere <bastienverdie    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 17:50:22 by basverdi          #+#    #+#             */
/*   Updated: 2024/03/12 23:35:52 by bastienverd      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *replace(char *str, char *search, char *replace)
{
	char *tmp;
	t_bool find;

	find = FALSE;
	while (str && search && *str && *search && *str == *search)
	{
		str++;
		search++;
		find = TRUE;
	}
	if (find)
	{
		tmp = ft_vjoin(2, "", replace, str);
		return (tmp);
	}
	else
		return (str);
}

char *get_logo(t_lst_envp *lst_envp)
{
	int os;
	char *logo;

	os = get_os(lst_envp);
	if (os == 0)
		logo = ft_strdup(LNX);
	if (os == 1)
		logo = ft_strdup(UBUNTU);
	if (os == 2)
		logo = ft_strdup(APPLE);
	if (os == 3)
		logo = ft_strdup(WINDOWS);
	return (logo);
}

char *smaller_pwd(char *pwd)
{
	char *res;
	char *rchr;

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

void get_branch(char **branch, char *config_file)
{
	char *line;
	int fd;
	char *tmp;

	fd = open(config_file, 0);
	line = get_next_line(fd);
	while (line)
	{
		if (!*branch && ft_strnstr(line, "branch", ft_strlen(line)))
		{
			tmp = ft_strchr(line, '"');
			if (!tmp)
				continue;
			*branch = ft_strdup(tmp + 1);
			*ft_strrchr(*branch, '"') = 0;
		}
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
}

t_bool is_git_file(char *pwd, char **branch)
{
	char *join;
	int access_git;
	char *smal_pwd;

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

char *get_prompt(t_lst_envp *lst_envp, char *prompt)
{
	char *pwd;
	char *new_pwd;
	char *home;
	char *logo;
	char *branch = NULL;

	logo = get_logo(lst_envp);
	pwd = get_envp_variable(lst_envp, "PWD");
	is_git_file(pwd, &branch);
	home = get_envp_variable(lst_envp, "HOME");
	new_pwd = replace(pwd, home, "~");
	prompt = ft_vjoin(25, "", GREY, BORDER_TOP, " ", DEFAULT, logo, " | ", GREEN,
					  "petite-coquille: ", DEFAULT, FOLDER, " ", CYAN, new_pwd, DEFAULT, " | ", GREEN, GIT, " ", BRANCH, " ", branch, " ", GREY,
					  BORDER_BOT, DEFAULT);
	free(branch);
	free(pwd);
	free(logo);
	free(new_pwd);
	if (home)
		free(home);
	return (prompt);
}
