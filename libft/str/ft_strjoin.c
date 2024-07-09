/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 08:46:47 by yroussea          #+#    #+#             */
/*   Updated: 2024/07/09 09:14:38 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	char	*result;

	j = 0;
	i = 0;
	if (!s1 || !s2)
		return (NULL);
	result = ft_calloc(sizeof(char), (1 + ft_strlen(s1) + ft_strlen(s2)));
	if (!result)
		return (NULL);
	while (s1 && s1[i])
	{
		result[i] = s1[i];
		i += 1;
	}
	while (s2 && s2[j])
	{
		result[i + j] = s2[j];
		j += 1;
	}
	return (result);
}

int	ft_str_str_len(char **str)
{
	int	i;

	i = 0;
	while (str && *str)
	{
		str += 1;
		i += 1;
	}
	return (i);
}

char	**ft_str_realloc(char **str)
{
	int		i;
	char	**result;

	i = ft_str_str_len(str);
	result = malloc((i + 2) * sizeof(char *));
	i = 0;
	while (str && str[i])
	{
		result[i] = ft_strdup(str[i]);
		i += 1;
	}
	result[i] = NULL;
	result[i + 1] = NULL;
	ft_free_split(str);
	return (result);
}
