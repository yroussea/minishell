/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 07:15:13 by yroussea          #+#    #+#             */
/*   Updated: 2023/11/07 07:34:20 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strdup(const char *s)
{
	int		i;
	char	*result;

	i = 0;
	if (!s || !*s)
		return (NULL);
	while (s && s[i])
		i += 1;
	result = ft_calloc(sizeof(char), (i + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (s && s[i])
	{
		result[i] = s[i];
		i += 1;
	}
	return (result);
}
