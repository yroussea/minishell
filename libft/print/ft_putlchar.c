/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putlchar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 08:12:52 by yroussea          #+#    #+#             */
/*   Updated: 2023/11/05 14:53:35 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_putlchar_fd(int c, int fd)
{
	write(fd, &c, 1);
	return (1);
}

size_t	ft_putlchar(int c)
{
	return (ft_putlchar_fd(c, 1));
}
