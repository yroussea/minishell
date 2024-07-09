/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 08:49:52 by yroussea          #+#    #+#             */
/*   Updated: 2024/07/09 09:14:38 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;
	int		cmp;

	cmp = 0;
	i = 0;
	if (!s1 && !s2)
		return (0);
	while (i < n)
	{
		cmp = *(unsigned char *)(s1 + i) - *(unsigned char *)(s2 + i);
		if (cmp != 0)
			return (cmp);
		i += 1;
	}
	return (0);
}
