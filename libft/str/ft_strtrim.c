/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 07:19:40 by yroussea          #+#    #+#             */
/*   Updated: 2024/07/09 09:14:38 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static size_t	ft_len_w_trim(char const *s1, char const *set, size_t *end)
{
	size_t	len;
	size_t	i;
	size_t	start;

	len = ft_strlen(s1);
	i = 0;
	start = 1;
	while (s1 && s1[i] && start)
	{
		if (!ft_strchr(set, s1[i]))
			break ;
		i += 1;
	}
	start = i;
	i = 0;
	while (s1 && s1[len - i - 1] && *end && (len - i > start))
	{
		if (!ft_strchr(set, s1[len - i - 1]))
			break ;
		i += 1;
	}
	*end = i;
	return (start);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*result;
	size_t	end;
	size_t	start;
	size_t	i;
	size_t	len;

	if (!s1 || !set)
		return (NULL);
	len = ft_strlen(s1);
	i = 0;
	end = 1;
	start = ft_len_w_trim(s1, set, &end);
	result = ft_calloc(sizeof(char), (len - end - start + 1));
	if (!result)
		return (NULL);
	while (i + start + end < len)
	{
		result[i] = s1[i + start];
		i += 1;
	}
	return (result);
}
