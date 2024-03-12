/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basverdi <basverdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 17:50:22 by basverdi          #+#    #+#             */
/*   Updated: 2024/03/12 21:05:30 by basverdi         ###   ########.fr       */
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

char	*ft_strdel_last(char *str)
{
	char	*tmp;
	size_t	i;

	tmp = "";
	i = 0;
	while (i < ft_strlen(str) - 1)
	{
		tmp[i] = str[i];
		i++;
	}
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

char	*get_prompt(t_lst_envp	*lst_envp)
{
	char	*pwd;
	char	*new_pwd;
	char	*prompt;
	char	*home;
	char	*logo;


	logo = get_logo(lst_envp);
	pwd = get_envp_variable(lst_envp, "PWD");
	home = get_envp_variable(lst_envp, "HOME");
	new_pwd = replace(pwd, home, "~");
	prompt = ft_vjoin(16, "", GREY, BORDER_TOP, " ", DEFAULT, logo, " | ", GREEN, \
		"petite-coquille: ", DEFAULT, FOLDER, " ", CYAN, new_pwd, GREY, \
		BORDER_BOT, DEFAULT);
	free(pwd);
	free(logo);
	free(new_pwd);
	if (home)
		free(home);
	return (prompt);
}
