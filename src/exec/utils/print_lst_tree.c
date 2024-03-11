/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_lst_tree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 17:30:04 by yroussea          #+#    #+#             */
/*   Updated: 2024/03/11 17:32:04 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_print_lst(int fd, t_lst *lst)
{
	while (lst)
	{
		ft_printf_fd(fd, "<%d>\n%S\n", lst->type, lst->cmd);
		lst = lst->next;
	}
}
