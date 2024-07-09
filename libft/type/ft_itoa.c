/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 09:16:16 by yroussea          #+#    #+#             */
/*   Updated: 2024/07/09 09:14:38 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static size_t	len_number(long int n)
{
	if (n > 9)
		return (1 + len_number(n / 10));
	return (1);
}

static char	*ft_neg_number(long int nb)
{
	size_t	len;
	size_t	i;
	char	*result;

	i = 0;
	len = len_number(nb) + 1;
	result = ft_calloc(sizeof(char), (len + 1));
	if (!result)
		return (NULL);
	result[0] = '-';
	while (i < len - 1)
	{
		result[len - i - 1] = nb % 10 + '0';
		nb = nb / 10;
		i += 1;
	}
	return (result);
}

char	*ft_itoa(int n)
{
	char		*result;
	size_t		i;
	size_t		len;

	i = 0;
	if (n >= 0)
	{
		len = len_number(n);
		result = ft_calloc(sizeof(char), (len + 1));
		if (!result)
			return (NULL);
		while (i < len)
		{
			result[len - i - 1] = n % 10 + '0';
			n = n / 10;
			i += 1;
		}
	}
	else
		result = ft_neg_number((long int)n * -1);
	return (result);
}
