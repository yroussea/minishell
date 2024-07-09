/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basverdi <basverdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:45:42 by basverdi          #+#    #+#             */
/*   Updated: 2024/07/09 09:16:14 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <unistd.h>

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
			get_set_exit_code(2, TRUE);
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
	get_set_exit_code(2, TRUE);
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
	exit(get_set_exit_code(0, FALSE));
}

void	exit_err(t_node *node, int fds)
{
	ft_printf_fd(fds, \
		"petite-coquille: exit: %s: numeric argument required\n", \
		node->args[1]);
	get_set_exit_code(2, TRUE);
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
		ft_printf_fd(fds, "petite-coquille: exit: too many arguments\n");
		get_set_exit_code(1, TRUE);
		if (!check_first_arg(node->args))
			free_exit(node);
		return ;
	}
	if (ft_str_str_len(node->args) == 2)
	{
		if (ft_overflow(node->args[1]) || !check_evry_arg(node->args))
			exit_err(node, fds);
		get_set_exit_code(ft_atoll(node->args[1]) % 256, TRUE);
	}
	free_exit(node);
}
