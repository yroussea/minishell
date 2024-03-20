/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basverdi <basverdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:50:00 by yroussea          #+#    #+#             */
/*   Updated: 2024/03/20 16:57:17 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <sys/select.h>

t_bool	exec_pipe(t_node *node, t_lst_envp *envp, t_stack_id *stk_pid, t_fds fds)
{
	int		fd_pipe[2];

	if (ft_pipe(fd_pipe) < 0)
		return (ERROR);
	fds.in = 0;
	fds.out = fd_pipe[1];
	exec_tree(node->left, envp, stk_pid, fds);
	fds.in = fd_pipe[0];
	fds.out = 1;
	exec_tree(node->right, envp, stk_pid, fds);
	//wait la pipeline?
	if (ft_close(2, fd_pipe[0], fd_pipe[1]) < 0)
		return (ERROR);
	return (TRUE);
}

t_bool	exec_and(t_node *node, t_lst_envp *envp, t_stack_id *stk_pid, t_fds fds)
{
	/*(si dans pipe faire la suite dans un fork puis exit)
	 * dup2 entrer (si pas STDIN)
	 * exectree pour la gauche
	 * recup depuis la pile le pid
	 * close les pipes
	 * wait le fils
	 * si le fils a reussit (global ig)
	 * ->executer a droite
	 */
	(void)node;
	(void)envp;
	(void)stk_pid;
	(void)fds;
	return (ERROR);
}

t_bool	exec_or(t_node *node, t_lst_envp *envp, t_stack_id *stk_pid, t_fds fds)
{
	/*(si dans pipe faire la suite dans un fork puis exit)
	 * dup2 entrer (si pas STDIN)
	 * exectree pour la gauche
	 * recup depuis la pile le pid
	 * close les pipes
	 * wait le fils
	 * si le fils a echouer (global ig)
	 * ->executer a droite
	 */
	(void)node;
	(void)envp;
	(void)stk_pid;
	(void)fds;
	return (ERROR);
}

t_bool	exec_cmd(t_node *node, t_lst_envp *envp, t_stack_id *stk_pid, t_fds fds)
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
		envp_char = envp_to_char(envp);
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
	(void)stk_pid;
	(void)fds;
	return (ERROR);
}

t_bool	exec_tree(t_node *node, t_lst_envp *envp, t_stack_id *stk_pid, t_fds fds)
{
	ft_print_tree(node);
	(void)envp;
	(void)stk_pid;
	(void)fds;
/*	if (node->type == PIPE)
		exec_pipe(node, envp, stk_pid, fds);
	if (node->type == AND)
		exec_and(node, envp, stk_pid, fds);
	if (node->type == OR)
		exec_or(node, envp, stk_pid, fds);
	if (node->type == CMD)
		exec_cmd(node, envp, stk_pid, fds);*/
	return (FALSE);
}
