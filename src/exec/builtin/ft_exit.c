/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basverdi <basverdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:45:42 by basverdi          #+#    #+#             */
/*   Updated: 2024/03/28 18:03:05 by basverdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

extern int	g_exitcode;

void	ft_exit(t_node *node)
{
	int	code;

	code = 0;
	if (ft_str_str_len(node->args) > 1)
	{
		ft_printf_fd(node->outfile, "bash: exit: too many arguments\n");
		g_exitcode = 1;
		exit(0);
	}
	else if (ft_str_str_len(node->args) == 1)
	{
		code = ft_atoll(*node->args);
		g_exitcode = code % 256;
	}
	ft_printf_fd(node->outfile, "exit\n");
	exit(0);
}
