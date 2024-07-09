/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putlhexa.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 12:13:32 by yroussea          #+#    #+#             */
/*   Updated: 2024/07/09 09:14:38 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static size_t	annexhexa(int c, int fd, char letter_a)
{
	if (c < 10)
		return (ft_putlchar_fd(c + '0', fd));
	return (ft_putlchar_fd(letter_a + c - 10, fd));
}

size_t	ft_putlhexa_low_fd(unsigned long int nb, int fd)
{
	if (nb >= 16)
		return (ft_putlhexa_low_fd(nb / 16, fd) + annexhexa(nb % 16, fd, 'a'));
	return (annexhexa(nb, fd, 'a'));
}

size_t	ft_putlhexa_up_fd(unsigned long int nb, int fd)
{
	if (nb >= 16)
		return (ft_putlhexa_up_fd(nb / 16, fd) + annexhexa(nb % 16, fd, 'A'));
	return (annexhexa(nb, fd, 'A'));
}

size_t	ft_putlhexa_low(unsigned long int nb)
{
	return (ft_putlhexa_low_fd(nb, 1));
}

size_t	ft_putlhexa_up(unsigned long int nb)
{
	return (ft_putlhexa_up_fd(nb, 1));
}
