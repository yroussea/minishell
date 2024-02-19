/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 10:00:10 by yroussea          #+#    #+#             */
/*   Updated: 2023/11/07 07:27:19 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

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
