/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basverdi <basverdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 17:50:22 by basverdi          #+#    #+#             */
/*   Updated: 2024/03/12 18:17:26 by basverdi         ###   ########.fr       */
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

char	*get_prompt(t_lst_envp	*lst_envp)
{
	char	*pwd;
	char	*prompt;
	char	*home;

	pwd = get_envp_variable(lst_envp, "PWD");
	home = get_envp_variable(lst_envp, "HOME");
	pwd = replace(pwd, home, "~");
	prompt = ft_vjoin(3, "", "petite-coquille:", pwd, "\n >");
	free(pwd);
	return (prompt);
}