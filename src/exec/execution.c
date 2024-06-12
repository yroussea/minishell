/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basverdi <basverdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 21:28:36 by yroussea          #+#    #+#             */
/*   Updated: 2024/06/12 17:57:42 by basverdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_exitcode;

void	manage_error_on_split(char **error, t_lst_cmd *lst, t_lst_ope **ope)
{
	static char		*type_of_node[4] = {"42", "|", "&&", "||"};

	ft_lst_ope_add(ope, -1);
	if (!*error && lst)
		*error = ft_strdup(type_of_node[lst->type]);
	else if (!*error)
		*error = ft_strdup("newline");
	ft_printf_fd(2, "%s `%s`\n", "syntax error close to", *error);
	g_exitcode = 2;
	free(*error);
}

t_bool	split_two_lst(
	t_lst_cmd *lst,
	t_lst_ope **ope,
	t_lst_com **cmd,
	t_bool tmp)
{
	static char		*type_of_node[4] = {"42", "|", "&&", "||"};
	char			*error;

	error = NULL;
	while (lst || tmp == -1)
	{
		if (tmp == -1)
			manage_error_on_split(&error, lst, ope);
		if (tmp == -1)
			return (TRUE);
		if ((lst->type == CMD && !only_space(lst->cmd)) || lst->type > OR)
			ft_lst_com_add(cmd, lst->cmd);
		if ((lst->type == CMD && !only_space(lst->cmd)) || lst->type > OR)
			tmp = -1 * invalide_redir_sep(lst_com_pop(cmd)->redir, &error);
		else if (lst->type != CMD)
		{
			tmp = (tmp || !*cmd) * -2 + 1;
			if (tmp == -1)
				error = ft_strdup(type_of_node[lst->type]);
			else
				ft_lst_ope_add(ope, lst->type);
		}
		lst = lst->next;
	}
	return (TRUE);
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

t_bool	create_tree(t_node **root, t_lst_com *cmd, t_lst_ope *ope, \
t_lst_envp **envp)
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

void	execution(t_lst_cmd *lst, t_lst_envp **envp, t_data_stk *stks)
{
	t_lst_ope		*operator;
	t_lst_com		*cmd;
	t_node			*root;
	t_fds			fds;

	operator = NULL;
	cmd = NULL;
	root = NULL;
	fds = (t_fds){0, 1};
	if (!lst || !split_two_lst(lst, &operator, &cmd, 0))
		return ;
	ft_lst_cmd_free(lst);
	ft_get_lsts(operator, cmd, TRUE, FALSE);
	if (create_tree(&root, cmd, operator, envp) == FALSE)
		return ;
	if (verif_complete_tree(root))
	{
		exec_tree(root, NO_PIPE, stks, fds);
		wait_all(stks->pids, -1);
	}
	else
	{
		ft_printf_fd(2, "syntax error: Uncomplete line\n");
		g_exitcode = 2;
	}
}

void	exec(t_lst_cmd *lst, t_lst_envp **envp)
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
		execution(lst, envp, stks);
		ft_get_root(NULL, FALSE, TRUE);
		free(stks);
	}
	else
		ft_lst_cmd_free(lst);
	ft_get_lsts(NULL, NULL, FALSE, TRUE);
}
