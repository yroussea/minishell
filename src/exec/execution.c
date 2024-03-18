/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 21:28:36 by yroussea          #+#    #+#             */
/*   Updated: 2024/03/18 15:42:14 by yroussea         ###   ########.fr       */
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

void	exec(t_lst_cmd *lst_all)
{
	t_lst_ope	*operator;
	t_lst_com	*cmd;
	t_node		*root;

	/*pre parsing : "&& &&" (faire attention au ; et au () ) + operateur au
	 * debut / fin, c la merde
	 * pareil pour les redirection dc
	*/
	operator = NULL;
	cmd = NULL;
	root = NULL;
	if (!split_two_lst(lst_all, &operator, &cmd))
		return ;
	//ft_print_com(STDOUT_FILENO, cmd);
	//ft_print_ope(STDOUT_FILENO, operator);
	if (ft_add_all_branch(&root, operator))
		ft_add_all_leaf(&root, cmd);
	ft_print_tree(root);
	ft_free_tree(root);
	ft_lst_cmd_free(lst_all);
	ft_lst_com_free(cmd);
	ft_lst_ope_free(operator);
}
