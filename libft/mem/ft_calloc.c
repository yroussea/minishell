/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 10:00:10 by yroussea          #+#    #+#             */
/*   Updated: 2024/07/13 17:51:18 by basverdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	**ft_realloc_strs(char **str)
{
	int		i;
	char	**r;

	i = ft_str_str_len(str);
	if (!str)
		return (NULL);
	r = ft_calloc(sizeof(char *), (i + 2));
	if (!r)
	{
		ft_magic_free("%2", str);
		return (NULL);
	}
	i = 0;
	while (str[i])
	{
		r[i] = str[i];
		i++;
	}
	free(str);
	return (r);
}

void	*ft_calloc(size_t nmeb, size_t size)
{
	char	*array;
	size_t	i;

	i = 0;
	if (size == 0 || nmeb == 0)
		return (malloc(1));
	if ((long long)size < 0 || (long long)nmeb < 0)
		return (NULL);
	array = malloc(size * nmeb);
	if (!array)
		return (NULL);
	while (i < nmeb * size)
	{
		array[i] = '\0';
		i += 1;
	}
	return (array);
}
