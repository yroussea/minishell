/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 12:44:52 by yroussea          #+#    #+#             */
/*   Updated: 2024/07/09 09:14:38 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	len;
	char	*result;

	if (!s || !f)
		return (NULL);
	len = ft_strlen(s);
	result = ft_calloc(sizeof(char), (len + 1));
	if (!result)
		return (NULL);
	len = 0;
	while (s && s[len])
	{
		result[len] = f(len, s[len]);
		len += 1;
	}
	return (result);
}
