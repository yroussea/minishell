/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basverdi <basverdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 18:51:16 by basverdi          #+#    #+#             */
/*   Updated: 2024/06/12 19:05:26 by basverdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	set_sig_fork(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handler_exec);
	signal(SIGQUIT, handler_exec);
}

t_bool	verif_complete_tree(t_node *root)
{
	if (!root)
		return (FALSE);
	if (root->type == PIPE || root->type == AND || root->type == OR)
		return (verif_complete_tree(root->left) && \
			verif_complete_tree(root->right));
	return (TRUE);
}
