/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basverdi <basverdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 10:23:53 by yroussea          #+#    #+#             */
/*   Updated: 2024/03/19 15:45:58 by basverdi         ###   ########.fr       */
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

t_bool	exec_heredoc(char *buf, char *eof)
{
	int		fd;
	pid_t	pid;
	char	*line;
	char	*tmp;

	fd = open(buf, 577);
	pid = fork();
	while (pid == 0)
	{
		line = readline("> ");
		if (ft_strncmp(line, eof, ft_strlen(eof) + 1) != 0)
		{
			tmp = ft_vjoin(2, "", line, "\n");
			ft_putstr_fd(tmp, fd);
			free(tmp);
		}
		else
			break ;
	}
	waitpid(pid, NULL, 0);
	close(fd);
	if (unlink(buf))
		return (FALSE);
	return (TRUE);
}

char	*ft_heredoc(char *eof)
{
	char	*buf;
	int		i;

	buf = ft_calloc(19, sizeof(char));
	if (!buf)
		return (NULL);	
	ft_strlcat(buf, "heredoc_", 9);
	i = 8;
	while (i < 18)
		buf[i++] = ft_random();
	exec_heredoc(buf, eof);
	return (buf);
}
