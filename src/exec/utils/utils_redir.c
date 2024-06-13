/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basverdi <basverdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 18:01:15 by basverdi          #+#    #+#             */
/*   Updated: 2024/06/13 16:26:06 by basverdi         ###   ########.fr       */
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
	chdir(path);
	if (errno == ENOENT)
	{
		ft_printf_fd(node->outfile, "cd: stale file handle: %s\n", path);
		get_set_exit_code(1);
	}
	get_new_pwd(node, 0);
	get_new_pwd(node, 1);
	get_set_exit_code(errno);
	cd_err(node);
}