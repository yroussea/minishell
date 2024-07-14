/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_out_quote.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 13:23:16 by yroussea          #+#    #+#             */
/*   Updated: 2024/07/14 19:23:36 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static size_t	ft_len_split(char const *s, char *c)
{
	size_t	i;
	size_t	k;

	k = 1;
	if (ft_strchr(c, *s))
		k = 0;
	i = 1;
	if (!s[0])
		return (0);
	while (s && s[i])
	{
		if (!ft_strchr(c, s[i]) && ft_strchr(c, s[i - 1]))
			k += 1;
		i += 1;
	}
	return (k);
}

static size_t	ft_len_next_w(char const *s, char *c, size_t j, char quote)
{
	int	inside;

	inside = 0;
	j = 0;
	while (s && s[j])
	{
		if (s[j] == quote)
			inside = 1 - inside;
		if (!inside && ft_strchr(c, s[j]))
			break ;
		j += 1;
	}
	return (j);
}

static char	**fill_split(char const *s, char *c, char **result, char quote)
{
	size_t	k;
	size_t	i;
	size_t	j;

	i = 0;
	k = 0;
	while (s && s[i])
	{
		j = ft_len_next_w(s + i, c, j, quote);
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

char	**ft_split_out_quote(char const *s, char *c, char quote)
{
	char	**result;

	if (!s)
		return (NULL);
	result = ft_calloc(sizeof(char *), (ft_len_split(s, c) + 1));
	if (!result)
		return (NULL);
	return (fill_split(s, c, result, quote));
}
