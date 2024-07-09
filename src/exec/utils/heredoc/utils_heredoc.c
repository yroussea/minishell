/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basverdi <basverdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 13:44:41 by basverdi          #+#    #+#             */
/*   Updated: 2024/07/09 09:16:14 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	free_heredoc(t_bool reset, char *eof, int fd)
{
	static char		*limit = NULL;
	static int		fd_file;

	if (reset)
	{
		fd_file = fd;
		limit = eof;
	}
	else
	{
		free(limit);
		ft_close(1, fd_file);
	}
}
