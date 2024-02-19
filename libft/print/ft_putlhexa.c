/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putlhexa.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 12:13:32 by yroussea          #+#    #+#             */
/*   Updated: 2023/11/05 13:55:20 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static size_t	ft_putlchar_hexa_low(int c)
{
	if (c < 10)
		return (ft_putlchar(c + '0'));
	return (ft_putlchar('a' + c - 10));
}

static size_t	ft_putlchar_hexa_up(int c)
{
	if (c < 10)
		return (ft_putlchar(c + '0'));
	return (ft_putlchar('A' + c - 10));
}

size_t	ft_putlhexa_low(unsigned long int nb)
{
	if (nb >= 16)
		return (ft_putlhexa_low(nb / 16) + ft_putlchar_hexa_low(nb % 16));
	return (ft_putlchar_hexa_low(nb));
}

size_t	ft_putlhexa_up(unsigned long int nb)
{
	if (nb >= 16)
		return (ft_putlhexa_up(nb / 16) + ft_putlchar_hexa_up(nb % 16));
	return (ft_putlchar_hexa_up(nb));
}
