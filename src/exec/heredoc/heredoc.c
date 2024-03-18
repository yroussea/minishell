/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basverdi <basverdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 10:23:53 by yroussea          #+#    #+#             */
/*   Updated: 2024/03/18 18:20:22 by basverdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	ft_random()
{
	char	buf[1];
	int		fd;

	fd = open("/dev/random", 0);
	read(fd, buf, 1);
	close(fd);
	return (97 + ft_abs(*buf % 26));
}

char	*ft_heredoc(char *eof)
{
	char	*buf;
	int		i;
	int		fd2;

	(void)eof;
	buf = ft_calloc(19, sizeof(char));
	if (!buf)
		return (NULL);	
	ft_strlcat(buf, "heredoc_", 9);
	i = 8;
	while (i < 18)
		buf[i++] = ft_random();
	fd2 = open(buf, 577);
	return (buf);
}
