/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basverdi <basverdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 18:18:07 by yroussea          #+#    #+#             */
/*   Updated: 2024/05/01 16:55:32 by basverdi         ###   ########.fr       */
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
