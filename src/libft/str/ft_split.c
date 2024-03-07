/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 08:04:16 by yroussea          #+#    #+#             */
/*   Updated: 2023/11/08 06:55:37 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static size_t	ft_len_split(char const *s, char c)
{
	size_t	i;
	size_t	k;

	k = 1;
	if (s[0] == c)
		k = 0;
	i = 1;
	if (!s[0])
		return (0);
	while (s && s[i])
	{
		if (s[i] != c && s[i - 1] == c)
			k += 1;
		i += 1;
	}
	return (k);
}

static size_t	ft_len_next_w(char const *s, char c, size_t j)
{
	j = 0;
	while (s && s[j] && s[j] != c)
		j += 1;
	return (j);
}

static char	**fill_split(char const *s, char c, char **result)
{
	size_t	k;
	size_t	i;
	size_t	j;

	i = 0;
	k = 0;
	while (s && s[i])
	{
		j = ft_len_next_w(s + i, c, j);
		if (j != 0)
		{
			result[k] = ft_calloc(sizeof(char), (j + 1));
			if (!result)
			{
				ft_free_split(result);
				return (NULL);
			}
			ft_strlcpy(result[k], s + i, j + 1);
			i += j - 1;
			k += 1;
		}
		i += 1;
	}
	return (result);
}

char	**ft_split(char const *s, char c)
{
	char	**result;

	if (!s)
		return (NULL);
	result = ft_calloc(sizeof(char *), (ft_len_split(s, c) + 1));
	if (!result)
		return (NULL);
	return (fill_split(s, c, result));
}
