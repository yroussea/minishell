/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 16:18:45 by yroussea          #+#    #+#             */
/*   Updated: 2024/07/09 09:14:38 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;

	if (!dest && !src)
		return (dest);
	i = 0;
	if (dest > src)
	{
		while (i < n)
		{
			i += 1;
			*(unsigned char *)(dest + n - i) = *(unsigned char *)(src + n - i);
		}
	}
	else
	{
		while (i < n)
		{
			*(unsigned char *)(dest + i) = *(unsigned char *)(src + i);
			i += 1;
		}
	}
	return (dest);
}
