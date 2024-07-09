/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 09:05:39 by yroussea          #+#    #+#             */
/*   Updated: 2024/07/09 09:14:38 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	k;

	i = 0;
	if (len == 0 && !big)
		return (NULL);
	if (!little || *little == '\0' || little == big)
		return ((char *)big);
	while (big[i] && i < len)
	{
		k = 0;
		while (little[k] == big[i + k] && (i + k) < len && little[k] && big[k])
			k += 1;
		if (!little[k] && k != 0)
			return ((char *)(big + i));
		i += 1;
	}
	return (NULL);
}
