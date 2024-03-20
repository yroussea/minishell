/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 21:28:36 by yroussea          #+#    #+#             */
/*   Updated: 2024/03/20 18:14:03 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_bool	split_two_lst(t_lst_cmd *lst_all, t_lst_ope **ope, t_lst_com **cmd)
{
	t_type_of_node	type;

	if (!lst_all)
		return (FALSE);
	while (lst_all)
	{
		type = lst_all->type;
		if (type < PIPE || type > OR)
			ft_lst_com_add(cmd, lst_all->cmd);
		else
			ft_lst_ope_add(ope, type);
		lst_all = lst_all->next;
	}
	return (TRUE);
}

t_data_stk	*init_stks(void)
{
	t_stack_pipe	*stk_pipe;
	t_stack_id		*stk_pid;
	t_data_stk		*new;

	new = malloc(sizeof(t_data_stk));
	if (!new)
		return (NULL);
	stk_pipe = NULL;
	new->pipes = &stk_pipe;
	stk_pid = NULL;
	new->pids = &stk_pid;
	return (new);
}

void	exec(t_lst_cmd *lst_all, t_lst_envp *envp)
{
	t_lst_ope	*operator;
	t_lst_com	*cmd;
	t_node		*root;
	t_data_stk	*stks;
	t_fds		fds;

	/*pre parsing : "&& &&" (faire attention au ; et au () ) + operateur au
	 * debut / fin, c la merde
	 * pareil pour les redirection dc
	*/
	operator = NULL;
	cmd = NULL;
	root = NULL;
	stks = init_stks();
	if (stks)
	{
		fds.in = 0;
		fds.out = 1;
		if (!split_two_lst(lst_all, &operator, &cmd))
			return ;
		if (ft_add_all_branch(&root, operator))
			ft_add_all_leaf(&root, cmd);
		exec_tree(root, envp, stks, fds);
		ft_free_tree(root);
	}
	ft_lst_com_free(cmd);
	ft_lst_ope_free(operator);
	ft_lst_cmd_free(lst_all);
}
