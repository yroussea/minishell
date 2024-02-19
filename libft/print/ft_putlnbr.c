/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putlnbr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 08:37:22 by yroussea          #+#    #+#             */
/*   Updated: 2023/11/05 12:37:49 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_putlnbr(int n)
{
	if (n == -2147483648)
		return (ft_putlstr("-2147483648"));
	if (n < 0)
		return (ft_putlchar('-') + ft_putlnbr(n * -1));
	if (n < 10)
		return (ft_putlchar(n + '0'));
	return (ft_putlnbr(n / 10) + ft_putlchar(n % 10 + '0'));
}

size_t	ft_putlunbr(unsigned int n)
{
	if (n < 10)
		return (ft_putlchar(n + '0'));
	return (ft_putlnbr(n / 10) + ft_putlchar(n % 10 + '0'));
}
