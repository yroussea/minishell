/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basverdi <basverdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 21:28:36 by yroussea          #+#    #+#             */
/*   Updated: 2024/03/28 18:04:18 by basverdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_bool	split_two_lst(t_lst_cmd *lst_all, t_lst_ope **ope, t_lst_com **cmd)
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
			ft_lst_com_add(cmd, lst_all->cmd);
		else
			ft_lst_ope_add(ope, type);
		lst_all = lst_all->next;
	}
	return (TRUE);
}

t_data_stk	*init_stks(void)
{
	t_data_stk	*new;

	new = malloc(sizeof(t_data_stk));
	if (!new)
		return (NULL);
	return (new);
}

void	exec(t_lst_cmd *lst_all, t_lst_envp *envp)
{
	t_lst_ope		*operator;
	t_lst_com		*cmd;
	t_node			*root;
	t_data_stk		*stks;
	t_fds			fds;
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
	ft_get_stks(stks, TRUE, FALSE);
	ft_get_envp(envp, TRUE, FALSE);
	if (stks)
	{
		stk_pipe = NULL;
		stks->pipes = &stk_pipe;
		stk_pid = NULL;
		stks->pids = &stk_pid;
		fds.in = 0;
		fds.out = 1;
		if (!split_two_lst(lst_all, &operator, &cmd))
			return ;
		ft_lst_cmd_free(lst_all);
		ft_get_lsts(operator, cmd, TRUE, FALSE);
		if (ft_add_all_branch(&root, operator))
			ft_add_all_leaf(&root, cmd, &envp);
		exec_tree(root, FALSE, stks, fds);
		wait_all(stks->pids, -1);
		ft_get_root(NULL, FALSE, TRUE);
		free(stks);
	}
	else
		ft_lst_cmd_free(lst_all);
	ft_get_lsts(NULL, NULL, FALSE, TRUE);
}
