/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stackadd_back.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 13:11:27 by yroussea          #+#    #+#             */
/*   Updated: 2024/07/09 09:14:38 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_stackadd_back(t_stack **stack, t_stack *new)
{
	if (!stack || !new)
		return ;
	if (!(*stack))
		*stack = new;
	else if (!(*stack)->next)
		(*stack)->next = new;
	else
		ft_stackadd_back(&(*stack)->next, new);
}
