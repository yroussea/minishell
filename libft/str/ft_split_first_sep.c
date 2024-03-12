/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_first_sep.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 14:40:52 by yroussea          #+#    #+#             */
/*   Updated: 2024/03/12 15:14:28 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_char_in_str(char const *s, char c)
{
	while (s && *s)
	{
		if (*s == c)
			return (1);
		s++;
	}
	return (0);
}

static size_t	ft_len_next_w(char const *s, char c)
{
	int	i;

	i = 0;
	while (s && s[i] && s[i] != c)
		i++;
	return (i);
}

static char	**fill_split_fist_sep(char const *s, char c, char **result)
{
	int	j;
	int	k;

	j = 0;
	k = 0;
	while (s && *s)
	{
		j = ft_len_next_w(s, c);
		if (j != 0)
		{
			if (k == 1)
				j = ft_strlen(s);
			result[k] = ft_calloc(sizeof(char), j + 1);
			if (!result)
			{
				ft_free_split(result);
				return (NULL);
			}
			ft_strlcpy(result[k], s, j + 1);
			s += j - 1;
			k += 1;
		}
		s += 1;
	}
	return (result);
}

char	**ft_split_first_sep(char const *s, char c)
{
	char	**result;

	if (!s)
		return (NULL);
	result = ft_calloc(sizeof(char *), 2 + ft_char_in_str(s, c));
	if (!result)
		return (NULL);
	return (fill_split_fist_sep(s, c, result));
}
