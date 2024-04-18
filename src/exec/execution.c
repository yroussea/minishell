/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basverdi <basverdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 21:28:36 by yroussea          #+#    #+#             */
/*   Updated: 2024/04/18 14:32:59 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>

t_bool	only_space(char **strs)
{
	int	j;

	j = 0;
	while (strs && *strs)
	{
		while ((*strs)[j])
		{
			if ((*strs)[j] != ' ')
				return (FALSE);
			j += 1;
		}
		strs += 1;
	}
	return (TRUE);
}

t_bool	split_two_lst(t_lst_cmd *lst_all, t_lst_ope **ope, t_lst_com **cmd)
{
	t_type_of_node	type;
	t_bool			tmp;

	*ope = NULL;
	*cmd = NULL;
	tmp = 0;
	if (!lst_all)
		return (FALSE);
	while (lst_all)
	{
		if (lst_all->type == CMD && only_space(lst_all->cmd))
		{
			lst_all = lst_all->next;
			continue ;
		}
		type = lst_all->type;
		if (type < PIPE || type > OR)
		{
			ft_lst_com_add(cmd, lst_all->cmd);
			tmp = 0;
		}
		else
		{
			if (tmp)
			{
				ft_lst_ope_add(ope, -1);
				ft_printf_fd(2, "%s %s\n", "syntaxe error close to", \
					"{to-fill}"); //to-fill
				return (TRUE);
			}
			else
				ft_lst_ope_add(ope, type);
			tmp = 1;
		}
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

t_bool	verif_complete_tree(t_node *root)
{
	if (!root)
		return (FALSE);
	if (root->type == PIPE || root->type == AND || root->type == OR)
		return (verif_complete_tree(root->left) && \
			verif_complete_tree(root->right));
	return (TRUE);
}

t_bool	create_tree(t_node **root, t_lst_com *cmd, t_lst_ope *ope, t_lst_envp **envp)
{
	if (ft_add_all_branch(root, ope))
	{
		if (ft_add_all_leaf(root, cmd, envp) == ERROR)
		{
			ft_get_lsts(NULL, NULL, FALSE, TRUE);
			return (FALSE);
		}
	}
	return (TRUE);
}

void	execution(t_lst_cmd *lst_all, t_lst_envp **envp, t_data_stk *stks)
{
	t_lst_ope		*operator;
	t_lst_com		*cmd;
	t_node			*root;
	t_fds			fds;

	operator = NULL;
	cmd = NULL;
	root = NULL;
	fds = (t_fds){0, 1};
	if (!split_two_lst(lst_all, &operator, &cmd))
		return ;
	ft_lst_cmd_free(lst_all);
	ft_get_lsts(operator, cmd, TRUE, FALSE);
	if (create_tree(&root, cmd, operator, envp) == FALSE)
		return ;
	if (verif_complete_tree(root))
	{
		exec_tree(root, NO_PIPE, stks, fds);
		wait_all(stks->pids, -1);
	}
	else
		ft_printf_fd(2, "Uncomplete line\n");
}

void	exec(t_lst_cmd *lst_all, t_lst_envp **envp)
{
	t_data_stk		*stks;
	t_stack_pipe	*stk_pipe;
	t_stack_id		*stk_pid;

	stks = init_stks();
	ft_get_stks(stks, TRUE, FALSE);
	ft_get_envp(*envp, TRUE, FALSE);
	if (stks)
	{
		stk_pipe = NULL;
		stks->pipes = &stk_pipe;
		stk_pid = NULL;
		stks->pids = &stk_pid;
		execution(lst_all, envp, stks);
		ft_get_root(NULL, FALSE, TRUE);
		free(stks);
	}
	else
		ft_lst_cmd_free(lst_all);
	ft_get_lsts(NULL, NULL, FALSE, TRUE);
}
