/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_lst_tree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basverdi <basverdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 17:30:04 by yroussea          #+#    #+#             */
/*   Updated: 2024/03/14 21:31:49 by basverdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_print_lst(int fd, t_lst_cmd *lst)
{
	static char	*type[11] = {"CMD", "PIPE", "AND", "OR", "HEREDOC", "ADD", "FD_IN", "FD_OUT", "DIRE_TWO", "VARIABLE", "FLAG"};

	while (lst)
	{
		ft_printf_fd(fd, "<%s>\n%S\n", type[lst->type], lst->cmd);
		lst = lst->next;
	}
}
