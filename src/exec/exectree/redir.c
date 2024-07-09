/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basverdi <basverdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 17:23:57 by basverdi          #+#    #+#             */
/*   Updated: 2024/07/09 09:16:14 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	redir_heredoc(int fds_in, t_lst_redir *redir, t_lst_envp *lst_envp)
{
	if (fds_in != STDIN_FILENO)
		ft_close(1, fds_in);
	fds_in = redir->heredoc_fd;
	if (fds_in == -1)
		return (-1);
	if (no_replace_heredoc(redir->file) == FALSE)
		fds_in = heredoc_reopen(fds_in, lst_envp);
	return (fds_in);
}

int	redir_infile(int fds_in, t_lst_redir *redir)
{
	if (fds_in != STDIN_FILENO)
		ft_close(1, fds_in);
	fds_in = open(redir->file, 0);
	if (fds_in == -1)
		return (-1);
	return (fds_in);
}

int	redir_add(int fds_out, t_lst_redir *redir)
{
	if (fds_out != STDOUT_FILENO)
		ft_close(1, fds_out);
	fds_out = open(redir->file, O_CREAT | O_WRONLY | O_APPEND, 0664);
	if (fds_out == -1)
		return (-1);
	return (fds_out);
}

int	redir_out(int fds_out, t_lst_redir *redir)
{
	if (fds_out != STDOUT_FILENO)
		ft_close(1, fds_out);
	fds_out = open(redir->file, 577, 0664);
	if (fds_out == -1)
		return (-1);
	return (fds_out);
}

int	redir_error(int fds_error, t_lst_redir *redir)
{
	if (fds_error != STDERR_FILENO)
		ft_close(1, fds_error);
	fds_error = open(redir->file, 577, 0664);
	if (fds_error == -1)
		return (-1);
	return (fds_error);
}
