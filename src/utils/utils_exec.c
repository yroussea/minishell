/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basverdi <basverdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 18:51:16 by basverdi          #+#    #+#             */
/*   Updated: 2024/06/18 13:38:32 by basverdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	if (!WIFEXITED(status) && WCOREDUMP(status))
	{
		ft_printf_fd(STDERR_FILENO, "Quit (core dumped)\n");
		get_set_exit_code(131, TRUE);
	}
	if (WTERMSIG(status) == 2)
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