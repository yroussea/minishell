/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putlstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 08:14:11 by yroussea          #+#    #+#             */
/*   Updated: 2024/07/09 09:14:38 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_putlstr_fd(char *s, int fd)
{
	size_t	i;

	if (s == NULL)
	{
		(write(fd, "(null)", 6));
		return (6);
	}
	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i += ft_putlchar_fd(s[i], fd);
	return (i);
}

size_t	ft_putlstr(char *s)
{
	return (ft_putlstr_fd(s, 1));
}
