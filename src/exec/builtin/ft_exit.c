/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basverdi <basverdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:45:42 by basverdi          #+#    #+#             */
/*   Updated: 2024/03/27 19:20:23 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

extern int g_exitcode;

void ft_exit(t_node *node)
{
	int code;

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
		/*if (code > INT_MAX || code < INT_MIN)
			g_exitcode = 1;
		else*/ 
		if (code < 0)
			g_exitcode = code % 256;
		else if (code > 0 && code < 256)
			g_exitcode = code;
		else
			g_exitcode = 0;
	}
	ft_printf_fd(node->outfile, "exit\n");
	exit(0);
}
