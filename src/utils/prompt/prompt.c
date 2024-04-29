/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basverdi <basverdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 17:50:22 by basverdi          #+#    #+#             */
/*   Updated: 2024/04/29 13:31:18 by basverdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*replace(char *str, char *search, char *replace)
{
	char	*tmp;
	t_bool	find;

	find = FALSE;
	while (str && search && *str && *search && *str == *search)
	{
		str++;
		search++;
		find = TRUE;
	}
	if (find)
	{
		str++;
		tmp = ft_vjoin(2, "", replace, str);
		return (tmp);
	}
	else
		return (ft_strdup(str));
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

char	*get_user(t_lst_envp *lst_envp)
{
	char	*user;

	user = get_envp_variable(lst_envp, "USER");
	if (user)
		return (ft_vjoin(2, "", user, ":"));
	return (NULL);
}

char	*get_prompt(t_lst_envp *lst_envp, char *prompt)
{
	char	*pwd;
	char	*new_pwd;
	char	*home;
	char	*logo;
	char	*branch;

	branch = NULL;
	logo = get_logo(lst_envp);
	pwd = get_envp_variable(lst_envp, "PWD");
	is_git_file(pwd, &branch);
	home = get_envp_variable(lst_envp, "HOME");
	new_pwd = replace(pwd, home, "~/");
	if (!branch)
		prompt = ft_vjoin(11, "", DEFAULT, logo, DEFAULT, " | ", GREEN, FOLDER, \
			" ", new_pwd, " ", END, DEFAULT);
	else
		prompt = ft_vjoin(14, "", DEFAULT, logo, DEFAULT, " | ", GREEN, FOLDER, \
			" ", new_pwd, " ", DEFAULT, branch, CYAN, ") ", DEFAULT);
	ft_magic_free("%1 %1 %1 %1 %1", pwd, logo, new_pwd, branch, home);
	return (prompt);
}
