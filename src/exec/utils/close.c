/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 18:18:07 by yroussea          #+#    #+#             */
/*   Updated: 2024/03/22 18:17:37 by yroussea         ###   ########.fr       */
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
