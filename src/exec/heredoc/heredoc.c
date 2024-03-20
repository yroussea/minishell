/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basverdi <basverdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 10:23:53 by yroussea          #+#    #+#             */
/*   Updated: 2024/03/20 15:12:36 by basverdi         ###   ########.fr       */
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

t_bool sig_heredoc(char *line, char *eof, int count)
{
	char	*tmp;

	if (line == NULL)
	{
		tmp = ft_vjoin(5, "", \
			"petite-coquille: warning: here-document at line ", \
			ft_itoa(count + 1), " delimited by end-of-file (wanted `", \
			eof, "`)");
		ft_printf("%s\n", tmp);
		free(tmp);
		return (FALSE);
	}
	return (TRUE);
}

t_bool	exec_heredoc(char *eof, int fd)
{
	pid_t	pid;
	char	*line;
	char	*tmp;
	int		count;

	count = 0;
	pid = fork();
	while (pid == 0)
	{
		line = readline("> ");
		if (sig_heredoc(line, eof, count) == FALSE)
			exit(0);
		if (ft_strncmp(line, eof, ft_strlen(eof) + 1) != 0)
		{
			count++;
			tmp = ft_vjoin(2, "", line, "\n");
			ft_putstr_fd(tmp, fd);
			free(tmp);
		}
		else
			exit(0);
	}
	waitpid(pid, NULL, 0);
	return (TRUE);
}

char	*ft_heredoc(char *eof)
{
	int		fd;
	char	*buf;
	int		i;

	buf = ft_calloc(19, sizeof(char));
	if (!buf)
		return (NULL);	
	ft_strlcat(buf, "heredoc_", 9);
	i = 8;
	while (i < 18)
		buf[i++] = ft_random();
	fd = open(buf, 577);
	exec_heredoc(eof, fd);
	close(fd);
	if (unlink(buf))
	{
		free(buf);
		return (NULL);
	}
	free(buf);
	return (NULL);
}
