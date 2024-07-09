/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 08:10:07 by yroussea          #+#    #+#             */
/*   Updated: 2024/07/09 09:14:38 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	min(size_t a, size_t b)
{
	if (a < b)
		return (a);
	return (b);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*result;
	size_t	i;

	if (!s)
		return (NULL);
	if (start < ft_strlen(s))
	{
		result = ft_calloc(sizeof(char), (min(len, ft_strlen(s + start)) + 1));
		if (!result)
			return (NULL);
		i = 0;
		while (s && s[start + i] && i < len)
		{
			result[i] = s[start + i];
			i += 1;
		}
		return (result);
	}
	result = malloc(sizeof(char) * 1);
	if (!result)
		return (NULL);
	result[0] = '\0';
	return (result);
}
