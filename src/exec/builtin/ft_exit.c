/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basverdi <basverdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:45:42 by basverdi          #+#    #+#             */
/*   Updated: 2024/04/10 19:05:04 by basverdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

extern int	g_exitcode;

void	free_exit(void)
{
	ft_get_lsts(NULL, NULL, FALSE, TRUE);
	ft_get_stks(NULL, FALSE, TRUE);
	ft_get_root(NULL, FALSE, TRUE);
	ft_get_envp(NULL, FALSE, TRUE);
	clear_history();
	exit(g_exitcode);
}

void	ft_exit(t_node *node)
{
	int	code;

	code = 0;
	if (ft_str_str_len(node->args) > 2)
	{
		ft_printf_fd(node->outfile, "bash: exit: too many arguments\n");
		g_exitcode = 1;
		return ;
	}
	ft_printf_fd(node->outfile, "exit\n");
	if (ft_str_str_len(node->args) == 2)
	{
		if (ft_overflow(node->args[1]))
		{
			ft_printf_fd(node->outfile, "bash: exit: %s: numeric argument required\n", node->args[1]);
			g_exitcode = 2;
			free_exit();
		}
		code = ft_atoll(node->args[1]);
		g_exitcode = code % 256;
	}
	free_exit();
}
