/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stkpipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 17:47:58 by yroussea          #+#    #+#             */
/*   Updated: 2024/07/09 09:16:14 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	stk_pipe_add_front(t_stack_pipe **stk, t_stack_pipe *new)
{
	if (!new)
		return ;
	if ((*stk))
		new->next = (*stk);
	*stk = new;
}

t_stack_pipe	*stk_pipe_pop(t_stack_pipe **stk)
{
	t_stack_pipe	*tmp;

	if (!stk || !*stk)
		return (NULL);
	tmp = (*stk);
	*stk = (*stk)->next;
	return (tmp);
}

void	ft_stk_pipe_free(t_stack_pipe *stk)
{
	t_stack_pipe	*tmp;

	while (stk)
	{
		tmp = stk;
		stk = stk->next;
		free(tmp);
	}
}

t_stack_pipe	*init_stk_pipe(int fds_pipe[2])
{
	t_stack_pipe	*new;

	new = ft_calloc(1, sizeof(t_stack_pipe));
	if (!new)
		return (NULL);
	new->next = NULL;
	new->pipe[0] = fds_pipe[0];
	new->pipe[1] = fds_pipe[1];
	return (new);
}

t_bool	ft_stk_pipe_add(t_stack_pipe **stk, int fds_pipe[2])
{
	t_stack_pipe	*tmp;

	tmp = init_stk_pipe(fds_pipe);
	if (!tmp)
	{
		ft_stk_pipe_free(*stk);
		*stk = NULL;
		return (FALSE);
	}
	stk_pipe_add_front(stk, tmp);
	return (TRUE);
}
