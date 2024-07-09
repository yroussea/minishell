/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putlpoint.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 12:49:33 by yroussea          #+#    #+#             */
/*   Updated: 2024/07/09 09:14:38 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_putlpoint_fd(void *p, int fd)
{
	if (p == 0)
		return (ft_putlstr_fd("(nil)", fd));
	return (ft_putlstr_fd("0x", fd) + \
			ft_putlhexa_low_fd((unsigned long long)p, fd));
}

size_t	ft_putlpoint(void *p)
{
	return (ft_putlpoint_fd(p, 1));
}
