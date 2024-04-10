/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basverdi <basverdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 10:23:53 by yroussea          #+#    #+#             */
/*   Updated: 2024/04/10 16:59:38 by basverdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <readline/history.h>

extern int	g_exitcode;

char	ft_random(void)
{
	char	buf[1];
	int		fd;

	fd = open("/dev/random", 0);
	read(fd, buf, 1);
	ft_close(1, fd);
	return (97 + ft_abs(*buf % 26));
}

t_bool	sig_heredoc(char *line, char *eof, int count)
{
	char	*tmp;
	char	*nb;

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

void	ft_exit_heredoc(char *eof, int fd, char *line)
{
	free(line);
	free(eof);
	close(fd);
	exit(0);
}

t_bool	exec_heredoc(char *eof, int fd)
{
	pid_t	pid;
	char	*line;
	int		count;
	int		status;

	count = 0;
	pid = ft_fork();
	if (pid == 0)
	{
		free_heredoc(TRUE, eof, fd);
		ft_get_lsts(NULL, NULL, FALSE, TRUE);
		ft_get_stks(NULL, FALSE, TRUE);
		ft_get_root(NULL, FALSE, TRUE);
		ft_get_envp(NULL, FALSE, TRUE);
		clear_history();
		line = "";
		while (ft_strncmp(line, eof, ft_strlen(line) + 1) != 0)
		{
			signal(SIGINT, heredoc_handler);
			line = readline("> ");
			if (sig_heredoc(line, eof, count) == FALSE)
				ft_exit_heredoc(eof, fd, line);
			if (eof && ft_strncmp(line, eof, ft_strlen(eof) + 1) != 0)
			{
				count++;
				ft_printf_fd(fd, "%s\n", line);
			}
			else
				ft_exit_heredoc(eof, fd, line);
		}
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_exitcode = WEXITSTATUS(status);
	return (!g_exitcode);
}

int	ft_heredoc(char *eof)
{
	int		fd;
	char	buf[19];
	int		i;
	char	*word_end;

	word_end = ft_strdup(eof);
	ft_strlcpy(buf, ".heredoc", 9);
	i = 8;
	while (i < 18)
		buf[i++] = ft_random();
	buf[i] = 0;
	fd = open((char *)buf, 577, 0664);
	signal(SIGINT, SIG_IGN);
	if (!exec_heredoc(word_end, fd))
	{
		free(word_end);
		set_sigaction(0);
		unlink(buf);
		close(fd);
		return (-1);
	}
	close(fd);
	fd = open((char *)buf, 0);
	unlink(buf);
	free(word_end);
	set_sigaction(0);
	return (fd);
}
