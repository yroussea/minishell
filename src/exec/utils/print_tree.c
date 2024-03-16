/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basverdi <basverdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 17:34:34 by basverdi          #+#    #+#             */
/*   Updated: 2024/03/16 17:35:06 by basverdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_print_tree(t_node *root)
{
	if (!root || root->type == CMD)
		return ;
	ft_print_node(root);
	ft_print_tree(root->left);
	ft_print_tree(root->right);
}
