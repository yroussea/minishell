/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 17:50:22 by basverdi          #+#    #+#             */
/*   Updated: 2024/03/13 11:48:21 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		tmp = ft_vjoin(2, "", replace, str);
		return (tmp);
	}
	else
		return (str);
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
	new_pwd = replace(pwd, home, "~");
	prompt = ft_vjoin(19, "", GREY, BORDER_TOP, " ", DEFAULT, logo, " | ", \
		GREEN, "petite-coquille: ", DEFAULT, FOLDER, " ", CYAN, \
		new_pwd, DEFAULT, branch, " ", GREY, BORDER_BOT, DEFAULT);
	free(branch);
	free(pwd);
	free(logo);
	free(new_pwd);
	if (home)
		free(home);
	return (prompt);
}
