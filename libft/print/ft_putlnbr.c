/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putlnbr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 08:37:22 by yroussea          #+#    #+#             */
/*   Updated: 2024/07/09 09:14:38 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_putlnbr_fd(int n, int fd)
{
	if (n == -2147483648)
		return (ft_putlstr_fd("-2147483648", fd));
	if (n < 0)
		return (ft_putlchar_fd('-', fd) + ft_putlnbr_fd(n * -1, fd));
	if (n < 10)
		return (ft_putlchar_fd(n + '0', fd));
	return (ft_putlnbr_fd(n / 10, fd) + ft_putlchar_fd(n % 10 + '0', fd));
}

size_t	ft_putlnbr(int n)
{
	return (ft_putlnbr_fd(n, 1));
}

size_t	ft_putlunbr_fd(unsigned int n, int fd)
{
	if (n < 10)
		return (ft_putlchar_fd(n + '0', fd));
	return (ft_putlnbr_fd(n / 10, fd) + ft_putlchar_fd(n % 10 + '0', fd));
}

size_t	ft_putlunbr(unsigned int n)
{
	return (ft_putlunbr_fd(n, 1));
}
