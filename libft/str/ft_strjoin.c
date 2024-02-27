/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 08:46:47 by yroussea          #+#    #+#             */
/*   Updated: 2023/11/07 08:16:16 by yroussea         ###   ########.fr       */
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
