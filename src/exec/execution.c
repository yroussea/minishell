/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 21:28:36 by yroussea          #+#    #+#             */
/*   Updated: 2024/03/16 15:12:45 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_bool	split_two_lst(t_lst_cmd *lst_all, t_lst_ope **ope, t_lst_com **cmd)
{
	t_type_of_node	type;

	while (lst_all)
	{
		type = lst_all->type;
		if (type == CMD)
			ft_lst_com_add(cmd, lst_all->cmd); //securiter
		else
			ft_lst_ope_add(ope, type); //securiter
		lst_all = lst_all->next;
	}
	ft_print_com(STDOUT_FILENO, *cmd);
	ft_print_ope(STDOUT_FILENO, *ope);
	return (TRUE);
}

void	exec(t_lst_cmd *lst_all)
{
	t_lst_ope	*operator;
	t_lst_com	*cmd;

	/*pre parsing : "&& &&" (faire attention au ; et au () ) + operateur au
	 * debut / fin, c la merde
	*/
	ft_print_lst(STDOUT_FILENO, lst_all);
	operator = NULL;
	cmd = NULL;
	split_two_lst(lst_all, &operator, &cmd);
	ft_lst_cmd_free(lst_all);
	(void)cmd;
	(void)operator;
}
