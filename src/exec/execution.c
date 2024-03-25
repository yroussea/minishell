/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 21:28:36 by yroussea          #+#    #+#             */
/*   Updated: 2024/03/25 21:11:23 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_bool	split_two_lst(t_lst_cmd *lst_all, t_lst_ope **ope, t_lst_com **cmd, t_lst_envp *envp)
{
	t_type_of_node	type;

	*ope = NULL;
	*cmd = NULL;
	if (!lst_all)
		return (FALSE);
	while (lst_all)
	{
		type = lst_all->type;
		if (type < PIPE || type > OR)
			ft_lst_com_add(cmd, lst_all->cmd, envp);
		else
			ft_lst_ope_add(ope, type);
		lst_all = lst_all->next;
	}
	return (TRUE);
}

t_data_stk	*init_stks(void)
{
	t_data_stk		*new;

	new = malloc(sizeof(t_data_stk));
	if (!new)
		return (NULL);
	return (new);
}

t_node	*ft_get_root(t_node	*node, t_bool reset)
{
	static t_node	*root = NULL;

	if (reset)
		root = node;
	return (root);
}

void	exec(t_lst_cmd *lst_all, t_lst_envp *envp)
{
	t_lst_ope	*operator;
	t_lst_com	*cmd;
	t_node		*root;
	t_data_stk	*stks;
	t_fds		fds;
	t_stack_pipe	*stk_pipe;
	t_stack_id		*stk_pid;

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
		stk_pipe = NULL;
		stks->pipes = &stk_pipe;
		stk_pid = NULL;
		stks->pids = &stk_pid;
		fds.in = 0;
		fds.out = 1;
		if (!split_two_lst(lst_all, &operator, &cmd, envp))
			return ;
		if (ft_add_all_branch(&root, operator))
			ft_add_all_leaf(&root, cmd, &envp);
		ft_get_root(root, TRUE);
		exec_tree(root, FALSE, stks, fds);
		wait_all(stks->pids, -1);
		ft_get_root(NULL, TRUE);
		ft_free_tree(root);
		free(stks);
	}
	ft_lst_com_free(cmd);
	ft_lst_ope_free(operator);
	ft_lst_cmd_free(lst_all);
}
