/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basverdi <basverdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 10:23:53 by yroussea          #+#    #+#             */
/*   Updated: 2024/03/26 16:20:15 by basverdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

extern int g_exitcode;

char ft_random(void)
{
	char buf[1];
	int fd;

	fd = open("/dev/random", 0);
	read(fd, buf, 1);
	ft_close(1, fd);
	return (97 + ft_abs(*buf % 26));
}

t_bool sig_heredoc(char *line, char *eof, int count)
{
	char *tmp;
	char *nb;

	if (line == NULL)
	{
		nb = ft_itoa(count + 1);
		tmp = ft_vjoin(5, "",
					   "petite-coquille: warning: here-document at line ", nb,
					   " delimited by end-of-file (wanted `", eof, "`)");
		ft_printf("%s\n", tmp);
		ft_magic_free("%1 %1", tmp, nb);
		return (FALSE);
	}
	return (TRUE);
}

t_bool exec_heredoc(char *eof, int fd)
{
	pid_t pid;
	char *line;
	int count;
	int status;

	count = 0;
	pid = ft_fork();
	while (pid == 0)
	{
		signal(SIGINT, heredoc_handler);
		line = readline("> ");
		if (sig_heredoc(line, eof, count) == FALSE)
			exit(0);
		if (ft_strncmp(line, eof, ft_strlen(eof) + 1) != 0)
		{
			count++;
			ft_printf_fd(fd, "%s\n", line);
		}
		else
			exit(0);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_exitcode = WEXITSTATUS(status);
	return (TRUE);
}

int ft_heredoc(char *eof)
{
	int fd;
	char buf[19];
	int i;

	ft_strlcpy(buf, ".heredoc", 9);
	i = 8;
	while (i < 18)
		buf[i++] = ft_random();
	buf[i] = 0;
	fd = open((char *)buf, 577);
	signal(SIGINT, SIG_IGN);
	exec_heredoc(eof, fd);
	unlink(buf);
	set_sigaction(0);
	return (fd);
}
