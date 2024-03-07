/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stackadd_front.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 12:45:06 by yroussea          #+#    #+#             */
/*   Updated: 2023/11/03 13:39:34 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_stackadd_front(t_stack **stack, t_stack *new)
{
	if (!stack || !new)
		return ;
	if ((*stack))
		new->next = (*stack);
	*stack = new;
}
