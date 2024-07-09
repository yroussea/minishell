/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 07:28:11 by yroussea          #+#    #+#             */
/*   Updated: 2024/07/09 09:14:38 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	len_dst;
	size_t	len_src;

	len_src = ft_strlen(src);
	i = 0;
	if (size == 0)
		return (len_src);
	len_dst = ft_strlen(dst);
	if (size <= len_dst)
		return (size + len_src);
	while (src && src[i] && len_dst + i < size - 1)
	{
		dst[i + len_dst] = src[i];
		i += 1;
	}
	dst[i + len_dst] = '\0';
	return (len_dst + len_src);
}
