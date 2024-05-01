/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basverdi <basverdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 18:18:07 by yroussea          #+#    #+#             */
/*   Updated: 2024/05/01 18:06:36 by basverdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_close_pipe(t_stack_pipe **pipe)
{
	t_stack_pipe	*tmp;

	tmp = *pipe;
	while (tmp && tmp)
	{
		ft_close(2, tmp->pipe[0], tmp->pipe[1]);
		tmp = tmp->next;
	}
}

void	close_pipes(t_stack_pipe **stk_pipe)
{
	t_stack_pipe	*stk;

	stk = stk_pipe_pop(stk_pipe);
	if (!stk)
		return ;
	if (stk->pipe[0] > 2)
		ft_close(1, stk->pipe[0]);
	if (stk->pipe[1] > 2)
		ft_close(1, stk->pipe[1]);
	free(stk);
}

void	ft_close_command(t_node *node)
{
	if (!node)
		return ;
	if (node->infile > 2)
		close(node->infile);
	if (node->outfile > 2)
		close(node->outfile);
}
