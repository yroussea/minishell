/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putlpoint.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 12:49:33 by yroussea          #+#    #+#             */
/*   Updated: 2023/11/05 13:56:28 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_putlpoint(void *p)
{
	if (p == 0)
		return (ft_putlstr("(nil)"));
	return (ft_putlstr("0x") + ft_putlhexa_low((unsigned long long)p));
}
