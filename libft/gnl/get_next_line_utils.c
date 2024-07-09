/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 08:01:14 by yroussea          #+#    #+#             */
/*   Updated: 2024/07/09 09:14:38 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_find_bn(const char *s)
{
	long long	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\n')
			return (i);
		i += 1;
	}
	return (-1);
}

size_t	ft_strcpy_until_bn(const char *s, char *result)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != '\n')
	{
		(result)[i] = s[i];
		i += 1;
	}
	return (i);
}
