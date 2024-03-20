/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 18:18:07 by yroussea          #+#    #+#             */
/*   Updated: 2024/03/20 18:19:08 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_close_pipe(t_stack_pipe *pipe)
{
	while (pipe)
	{
		ft_close(2, pipe->pipe[0], pipe->pipe[1]);
		pipe = pipe->next;
	}
}
