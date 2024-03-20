/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 16:56:14 by yroussea          #+#    #+#             */
/*   Updated: 2024/03/20 20:18:47 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <unistd.h>

t_bool	all_redir_cmd(t_lst_redir *redir, t_fds fds)
{
	int	fds_error;

	fds_error = 2;
	while (redir)
	{
		if (redir->type == HEREDOC)
		{
			if (fds.in != STDIN_FILENO)
				ft_close(1, fds.in);
			fds.in = redir->heredoc_fd;
			if (fds.in == -1)
				break ;
		}
		if (redir->type == DIRE_IN)
		{
			if (fds.in != STDIN_FILENO)
				ft_close(1, fds.in);
			fds.in = open(redir->file, 0);
			if (fds.in == -1)
				break ;
		}
		if (redir->type == ADD)
		{
			if (fds.out != STDOUT_FILENO)
				ft_close(1, fds.out);
			fds.out = open(redir->file, O_CREAT | O_WRONLY | O_APPEND, 0664);
			if (fds.out == -1)
				break ;
		}
		if (redir->type == DIRE_OUT)
		{
			if (fds.out != STDOUT_FILENO)
			ft_close(1, fds.out);
			fds.out = open(redir->file, 577, 0664);
			if (fds.out == -1)
				break ;
		}
		if (redir->type == DIRE_TWO)
		{
			if (fds_error != STDERR_FILENO)
				ft_close(1, fds_error);
			fds_error = open(redir->file, 577, 0664);
			if (fds_error == -1)
				break ;
		}
		redir = redir->next;
	}
	if (fds_error == -1 || fds.in == -1 || fds.out == -1)
		return (FALSE);
	//dup2 !!!
	//close all
	return (TRUE);
}

t_bool	exec_cmd(t_node *node, t_bool from_pipe, t_data_stk *stks, t_fds fds)
{
	int		pid;
	char	**envp_char;
//difference buildin et cmd
	pid = ft_fork();
	if (pid < 0)
		return (ERROR);
	if (pid == 0)
	{
		//all redirection
		envp_char = envp_to_char(*node->envp);
		if (envp_char)
		{
			//remplirer cmd avec full path
			//make all redir (dup2)
			ft_close_pipe(*(stks)->pipes);
			execve(node->cmd, node->args, envp_char);
		}
		free(envp_char);
		exit(1);
	}
	//close cmd redir
	ft_stk_pid_add(stks->pids, pid);
	(void)stks;
	(void)fds;
	return (ERROR);
}
