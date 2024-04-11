/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basverdi <basverdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 18:19:47 by basverdi          #+#    #+#             */
/*   Updated: 2024/04/11 16:45:52 by basverdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

extern int	g_exitcode;

void	handler(int signal)
{
	if (signal == SIGINT)
	{
		ft_printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_exitcode = 130;
	}
	if (signal == SIGQUIT)
		return ;
}

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

void	heredoc_handler(int signal)
{
	if (signal == SIGINT)
	{
		ft_printf("\n");
		free_heredoc(FALSE, NULL, 0);
		exit(130);
	}
	if (signal == SIGQUIT)
		return ;
}

void	set_sigaction(int state)
{
	static struct termios	data;

	tcgetattr(0, &data);
	if (!state)
		data.c_lflag |= ECHOCTL;
	else
		data.c_lflag &= ~(ECHOCTL);
	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
}
