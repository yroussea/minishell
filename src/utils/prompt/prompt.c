/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basverdi <basverdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 17:50:22 by basverdi          #+#    #+#             */
/*   Updated: 2024/07/14 19:31:12 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*replace(char *str, char *search, char *replace)
{
	char	*tmp;
	t_bool	find;

	find = FALSE;
	tmp = str;
	while (str && search && *str && *search && *str == *search)
	{
		str++;
		search++;
		find = TRUE;
	}
	if (find && search && !*search)
	{
		if (*str)
			tmp = ft_vjoin(2, "", replace, ++str);
		else
			tmp = ft_strdup("~");
	}
	else
		tmp = ft_strdup(tmp);
	return (tmp);
}

char	*get_logo(t_lst_envp *lst_envp)
{
	int		os;
	char	*logo;

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

char	*get_prompt(t_lst_envp *lst_envp, char *prompt, int no_color)
{
	char	*pwd;
	char	*new_pwd;
	char	*home;
	char	*logo;
	char	*branch;

	branch = NULL;
	logo = get_logo(lst_envp);
	pwd = get_envp_variable(lst_envp, "PWD", 1);
	if (!pwd)
		pwd = get_envp_variable(lst_envp, "PWD", -2);
	is_git_file(pwd, &branch);
	home = get_envp_variable(lst_envp, "HOME", 0);
	new_pwd = replace(pwd, home, "~/");
	if (no_color)
		prompt = ft_vjoin(2, "", new_pwd, " > ");
	else if (!branch)
		prompt = ft_vjoin(11, "", DEFAULT, logo, DEFAULT, " | ", GREEN, FOLDER, \
			" ", new_pwd, " ", END, DEFAULT_END);
	else
		prompt = ft_vjoin(14, "", DEFAULT, logo, DEFAULT, " | ", GREEN, FOLDER, \
			" ", new_pwd, " ", DEFAULT, branch, CYAN, ") ", DEFAULT_END);
	ft_magic_free("%1 %1 %1 %1 %1", pwd, logo, new_pwd, branch, home);
	return (prompt);
}
