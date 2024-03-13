/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_lst_tree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 17:30:04 by yroussea          #+#    #+#             */
/*   Updated: 2024/03/13 11:57:25 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_print_lst(int fd, t_lst_cmd *lst)
{
	static char	*type[5] = {"CMD", "PIPE", "AND", "OR", "FDS"};

	while (lst)
	{
		ft_printf_fd(fd, "<%s>\n%S\n", type[lst->type], lst->cmd);
		lst = lst->next;
	}
}
