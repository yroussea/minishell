/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 16:56:14 by yroussea          #+#    #+#             */
/*   Updated: 2024/03/20 18:39:21 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_bool	exec_cmd(t_node *node, t_bool from_pipe, t_data_stk *stks, t_fds fds)
{
	int		pid;
	char	**envp_char;
//difference buildin et cmd
//node->cmd should be all path cmd
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
			//close all pipes
			//close all redir (carefull if no redir)
			execve(node->cmd, node->args, envp_char);
		}
		free(envp_char);
		exit(1);
	}
	//close cmd redir
	//stack_id_add(pid)
	(void)stks;
	(void)fds;
	return (ERROR);
}
