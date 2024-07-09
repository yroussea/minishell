/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basverdi <basverdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 14:23:58 by yroussea          #+#    #+#             */
/*   Updated: 2024/07/09 09:16:14 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_bool	ft_is_n(char *arg)
{
	if (!arg || *arg != '-' || (*arg && !*(arg + 1)))
		return (0);
	arg += 1;
	while (*(arg) == 'n')
		arg += 1;
	if (*arg)
		return (FALSE);
	return (TRUE);
}

void	ft_echo(t_node *node)
{
	char	**args;
	t_bool	n;

	args = node->args + 1;
	n = 1;
	if (args)
	{
		while (args && ft_is_n(*args))
		{
			args += 1;
			n = 0;
		}
		while (args && *args && *(args + 1))
		{
			ft_printf_fd(node->outfile, "%s ", *args);
			args += 1;
		}
		if (args && *args)
			ft_printf_fd(node->outfile, "%s", *args);
	}
	if (n)
		ft_printf_fd(node->outfile, "\n");
}
