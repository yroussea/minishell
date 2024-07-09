/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stacklast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 13:09:53 by yroussea          #+#    #+#             */
/*   Updated: 2024/07/09 09:14:38 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_stack	*ft_stackbeforelast(t_stack *stack)
{
	if (!stack)
		return (NULL);
	if (!stack->next)
		return (stack);
	if (!stack->next->next)
		return (stack);
	return (ft_stackbeforelast(stack->next));
}

t_stack	*ft_stacklast(t_stack *stack)
{
	if (!stack)
		return (NULL);
	if (!stack->next)
		return (stack);
	return (ft_stacklast(stack->next));
}
