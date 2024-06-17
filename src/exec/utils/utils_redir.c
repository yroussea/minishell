/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basverdi <basverdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 18:01:15 by basverdi          #+#    #+#             */
/*   Updated: 2024/06/17 17:59:24 by basverdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

void	move_to_dir(char *path, t_node *node)
{
	int	error;

	error = chdir(path);
	if (!error)
	{
		if (get_new_pwd(node, 0))
			get_new_pwd(node, 1);
	}
	cd_err(node, errno);
}

void	swap_unquate(char **str, t_lst_envp *envp, char **trimed, char **s)
{
	*trimed = ft_unquote(*str, envp, 0, NULL);
	*s = ft_strdupexept(*trimed, '\001');
	free(*trimed);
	*trimed = ft_strtrim(*s, " ");
}
