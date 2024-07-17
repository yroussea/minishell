/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basverdi <basverdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 18:51:16 by basverdi          #+#    #+#             */
/*   Updated: 2024/07/17 14:11:44 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

t_bool	verif_complete_tree(t_node *root)
{
	if (!root)
		return (FALSE);
	if (root->type == PIPE || root->type == AND || root->type == OR)
		return (verif_complete_tree(root->left) && \
			verif_complete_tree(root->right));
	return (TRUE);
}

void	check_status(int status)
{
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGQUIT)
	{
		if (WCOREDUMP(status))
			ft_printf_fd(STDERR_FILENO, "Quit (core dumped)\n");
		else
			ft_printf_fd(STDERR_FILENO, "Quit\n");
		get_set_exit_code(131, TRUE);
	}
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		ft_printf_fd(STDERR_FILENO, "\n");
		get_set_exit_code(130, TRUE);
	}
}

void	ft_clear_term(int ac, char **av)
{
	if (ac > 1 && ft_strncmp("--no-clear", av[1], 10))
	{
		if (!ft_strncmp(av[1], "--mini-coque", 12))
			ft_printf_fd(2, WELL_PLAYED, YELLOW, DEFAULT, EASTER_EGG, \
				BETTER_THAN_BASH);
		else if (!ft_strncmp(av[1], "--goat", 6))
			ft_printf_fd(2, AUTOR);
		else if (!ft_strncmp(av[1], "--42sh", 6))
			ft_printf_fd(2, MINISHORSH);
		else
			ft_printf_fd(2, "%sError%s\n%s", RED, DEFAULT, ERROR_ARGS);
		exit(42);
	}
	else if (ac == 1 || ft_strncmp("--no-clear", av[1], 10))
		ft_printf_fd(2, "\033c");
	else if (ac > 2)
	{
		ft_printf_fd(2, "%sError%s\n%s", RED, DEFAULT, ERROR_ARGS);
		exit(1);
	}
}

t_bool	is_forbidden(t_node *node, char *var)
{
	char	*tmp;

	tmp = var;
	if (!var || !*var)
		return (TRUE);
	if (!ft_isdigit(*var))
	{
		while (ft_isalnum(*var) || *var == '_')
			var += 1;
		if (!*var || (*var == '+' && !*(var + 1)))
			return (FALSE);
	}
	if (ft_strrchr(var, '+') == var + ft_strlen(var) - !!ft_strlen(var))
		tmp[ft_strlen(tmp) - !!ft_strlen(tmp)] = 0;
	ft_printf_fd(node->errorfile, \
			"petite-coquille: export: `%s': not a valid identifier\n", tmp);
	get_set_exit_code(1, TRUE);
	return (TRUE);
}

void	fake_pid(int exit_code, t_data_stk *stks)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		ft_close_pipe(stks->pipes);
		ft_get_envp(NULL, FALSE, TRUE);
		ft_get_root(NULL, FALSE, TRUE);
		ft_get_lsts(NULL, NULL, FALSE, TRUE);
		ft_get_stks(NULL, FALSE, TRUE);
		rl_clear_history();
		exit(exit_code);
	}
	ft_stk_pid_add(stks->pids, pid);
}
