/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stkpid.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 17:29:11 by yroussea          #+#    #+#             */
/*   Updated: 2024/07/09 09:16:14 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	stk_pid_add_front(t_stack_id **stk, t_stack_id *new)
{
	if (!stk || !new)
		return ;
	if ((*stk))
		new->next = (*stk);
	*stk = new;
}

int	stk_pid_pop(t_stack_id **stk)
{
	t_stack_id	*tmp;
	int			pid;

	if (!stk || !*stk)
		return (-1);
	tmp = (*stk);
	pid = tmp->pid;
	*stk = (*stk)->next;
	free(tmp);
	return (pid);
}

void	ft_stk_pid_free(t_stack_id *stk)
{
	t_stack_id	*tmp;

	while (stk)
	{
		tmp = stk;
		stk = stk->next;
		free(tmp);
	}
}

t_stack_id	*init_stk_pid(int s)
{
	t_stack_id	*new;

	new = ft_calloc(1, sizeof(t_stack_id));
	if (!new)
		return (NULL);
	new->next = NULL;
	new->pid = s;
	return (new);
}

t_bool	ft_stk_pid_add(t_stack_id **stk, int pid)
{
	t_stack_id	*tmp;

	tmp = init_stk_pid(pid);
	if (!tmp)
	{
		ft_stk_pid_free(*stk);
		return (FALSE);
	}
	stk_pid_add_front(stk, tmp);
	return (TRUE);
}
