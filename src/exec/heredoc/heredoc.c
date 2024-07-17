/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basverdi <basverdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 10:23:53 by yroussea          #+#    #+#             */
/*   Updated: 2024/07/17 13:17:53 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_exit_heredoc(char *eof, int fd, char *line)
{
	free(line);
	free(eof);
	close(fd);
	rl_clear_history();
	exit(0);
}

char	*init_pid(char *eof, int fd)
{
	free_heredoc(TRUE, eof, fd);
	ft_get_lsts(NULL, NULL, FALSE, TRUE);
	ft_get_stks(NULL, FALSE, TRUE);
	ft_get_root(NULL, FALSE, TRUE);
	ft_get_envp(NULL, FALSE, TRUE);
	rl_clear_history();
	return (NULL);
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
		line = init_pid(eof, fd);
		signal(SIGINT, heredoc_handler);
		while (!line || ft_strncmp(line, eof, ft_strlen(line) + 1) != 0)
		{
			line = readline("> ");
			if (sig_heredoc(line, eof, count) == FALSE)
				ft_exit_heredoc(eof, fd, line);
			if (eof && ft_strncmp(line, eof, ft_strlen(eof) + 1) != 0)
				ft_printf_fd(fd, "%s\n", line, count++);
			else
				ft_exit_heredoc(eof, fd, line);
		}
	}
	waitpid(pid, &status, 0);
	return (!get_set_exit_code(WEXITSTATUS(status), TRUE));
}

char	*end_word(char *eof)
{
	char	*str;
	int		i;

	i = 0;
	str = malloc(ft_strlen(eof) + 1);
	while (eof && *eof)
	{
		if (*eof != 34 && *eof != 39)
			str[i++] = *eof;
		eof += 1;
	}
	str[i] = 0;
	return (str);
}

int	ft_heredoc(char *eof)
{
	int		fd;
	char	buf[19];
	int		i;
	char	*word_end;

	word_end = end_word(eof);
	ft_strlcpy(buf, "/tmp/.heredoc", 9 + 5);
	i = 8 + 5;
	while (i < 18)
		buf[i++] = ft_random();
	buf[i] = 0;
	fd = open((char *)buf, 577, 0664);
	signal(SIGINT, SIG_IGN);
	if (fd == -1 || !exec_heredoc(word_end, fd))
	{
		free(word_end);
		unlink(buf);
		ft_close(1, fd);
		return (-1);
	}
	ft_close(1, fd);
	fd = open((char *)buf, 0);
	unlink(buf);
	free(word_end);
	return (fd);
}
