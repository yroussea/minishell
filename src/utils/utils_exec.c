/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basverdi <basverdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 18:51:16 by basverdi          #+#    #+#             */
/*   Updated: 2024/06/17 18:50:19 by basverdi         ###   ########.fr       */
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
