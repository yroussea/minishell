/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstack.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 07:36:40 by yroussea          #+#    #+#             */
/*   Updated: 2024/07/09 09:14:38 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_put_stack(t_stack *stack)
{
	size_t	i;
	t_stack	*tmp;

	i = 0;
	tmp = stack;
	i += ft_printf("top> ");
	while (tmp)
	{
		i += ft_printf("%d ", tmp->content);
		tmp = tmp->next;
	}
	i += ft_printf("\n");
	return (i);
}
