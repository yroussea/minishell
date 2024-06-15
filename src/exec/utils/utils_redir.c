/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basverdi <basverdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 18:01:15 by basverdi          #+#    #+#             */
/*   Updated: 2024/06/15 09:08:47 by yroussea         ###   ########.fr       */
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
