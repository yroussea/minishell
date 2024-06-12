/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basverdi <basverdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:45:42 by basverdi          #+#    #+#             */
/*   Updated: 2024/06/12 17:53:08 by basverdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <unistd.h>

extern int	g_exitcode;

t_bool	check_first_arg(char **args)
{
	int	i;

	i = 0;
	while (args[1][i])
	{
		if (i == 0 && args[1][i] == '-')
			i++;
		if (!ft_isnum(args[1][i]))
		{
			g_exitcode = 2;
			return (FALSE);
		}
		i++;
	}
	return (TRUE);
}

t_bool	check_evry_arg(char **args)
{
	int	i;
	int	j;

	i = 1;
	while (args[i])
	{
		j = 0;
		while (args[i][j])
		{
			if (!ft_isnum(args[i][j]) && args[i][j] != ' ')
				return (FALSE);
			j++;
		}
		i++;
	}
	g_exitcode = 2;
	return (TRUE);
}

void	free_exit(t_node *node)
{
	close_redir_builtin(node);
	ft_magic_free("%1 %2", node->cmd, node->args);
	ft_get_lsts(NULL, NULL, FALSE, TRUE);
	ft_close_pipe(ft_get_stks(NULL, FALSE, FALSE)->pipes);
	ft_get_stks(NULL, FALSE, TRUE);
	ft_get_root(NULL, FALSE, TRUE);
	ft_get_envp(NULL, FALSE, TRUE);
	rl_clear_history();
	exit(g_exitcode);
}

void	exit_err(t_node *node, int fds)
{
	ft_printf_fd(fds, \
		"petite-coquille: exit: %s: numeric argument required\n", \
		node->args[1], g_exitcode = 2);
	free_exit(node);
}

void	ft_exit(t_node *node, t_bool frompipe)
{
	int	fds;

	fds = 2;
	if (!frompipe)
		ft_printf_fd(node->errorfile, "exit\n");
	if (!frompipe)
		fds = node->errorfile;
	if (ft_str_str_len(node->args) > 2 && node->args[2])
	{
		if (ft_overflow(node->args[1]))
			exit_err(node, fds);
		ft_printf_fd(fds, "petite-coquille: exit: too many arguments\n", \
			g_exitcode = 1);
		if (!check_first_arg(node->args))
			free_exit(node);
		return ;
	}
	if (ft_str_str_len(node->args) == 2)
	{
		if (ft_overflow(node->args[1]) || !check_evry_arg(node->args))
			exit_err(node, fds);
		g_exitcode = ft_atoll(node->args[1]) % 256;
	}
	free_exit(node);
}
