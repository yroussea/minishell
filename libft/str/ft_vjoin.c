/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vjoin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:13:27 by yroussea          #+#    #+#             */
/*   Updated: 2024/07/09 09:14:38 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static size_t	ft_va_strlen(size_t nb_str, va_list args)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (j < nb_str)
	{
		i += ft_strlen(va_arg(args, char *));
		j += 1;
	}
	return (i);
}

char	*annex_vjoin(size_t nb_str, char *sep, va_list args)
{
	va_list	args_copy;
	size_t	total_len;
	char	*s;
	size_t	i;
	size_t	j;

	va_copy(args_copy, args);
	total_len = ft_va_strlen(nb_str, args_copy) + ft_strlen(sep) * (nb_str - 1);
	va_end(args_copy);
	s = ft_calloc(sizeof(char), total_len + 1);
	i = 0;
	j = 0;
	while (s && i < nb_str)
	{
		j += ft_strlcpy(s + j, va_arg(args, char *), total_len + 1);
		if (i != nb_str - 1)
			j += ft_strlcpy(s + j, sep, total_len + 1);
		i += 1;
	}
	*(s + j) = 0;
	return (s);
}

char	*ft_vjoin(size_t nb_str, char *sep, ...)
{
	va_list	args;
	char	*s;

	va_start(args, sep);
	s = annex_vjoin(nb_str, sep, args);
	va_end(args);
	return (s);
}
