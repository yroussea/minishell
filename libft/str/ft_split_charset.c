/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_charset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 09:46:53 by yroussea          #+#    #+#             */
/*   Updated: 2023/11/29 09:47:13 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_c_in_charset(char c, char *charset)
{
	int	i;

	i = 0;
	while (charset && charset[i] && charset[i] != c)
		i += 1;
	if (charset && charset[i])
		return (1);
	return (0);
}

void	ft_free_split(char **result)
{
	size_t	i;

	i = 0;
	while (result && result[i])
	{
		free(result[i]);
		i += 1;
	}
	free(result);
}

static size_t	ft_len_next_w_charset(char const *s, char *charset, size_t j)
{
	j = 0;
	while (s && s[j] && !ft_c_in_charset(s[j], charset))
		j += 1;
	return (j);
}

static char	**fill_split_charset(char const *s, char *charset, char **result)
{
	size_t	k;
	size_t	i;
	size_t	j;

	i = 0;
	k = 0;
	while (s && s[i])
	{
		j = ft_len_next_w_charset(s + i, charset, j);
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

char	**ft_split_charset(char const *s, char *charset)
{
	char	**result;
	size_t	i;
	size_t	k;

	if (!s)
		return (NULL);
	k = 1;
	if (ft_c_in_charset(s[0], charset))
		k = 0;
	i = 1;
	if (s && !s[0])
		return (0);
	while (s && s[i])
	{
		if (!ft_c_in_charset(s[i], charset) && \
			ft_c_in_charset(s[i - 1], charset))
			k += 1;
		i += 1;
	}
	result = ft_calloc(sizeof(char *), (k + 1));
	if (!result)
		return (NULL);
	return (fill_split_charset(s, charset, result));
}
