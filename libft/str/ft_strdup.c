/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basverdi <basverdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 07:15:13 by yroussea          #+#    #+#             */
/*   Updated: 2024/07/09 09:14:38 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strdup(const char *s)
{
	int		i;
	char	*res;

	i = 0;
	if (!s)
		return (NULL);
	i = ft_strlen(s);
	res = ft_calloc(sizeof(char), (i + 1));
	if (!res)
		return (NULL);
	ft_strlcpy(res, s, i + 1);
	return (res);
}

char	*ft_strdupexept(char *s, char c)
{
	int		i;
	char	*res;

	if (!s)
		return (NULL);
	i = 0;
	res = s;
	while (res && *res)
	{
		if (*res++ != c)
			i += 1;
	}
	res = ft_calloc(sizeof(char), (i + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (s && *s)
	{
		if (*s != c)
			res[i++] = *s;
		s += 1;
	}
	res[i] = 0;
	return (res);
}

char	*ft_strndup(const char *s, int n)
{
	int		i;
	char	*res;

	i = 0;
	if (!s)
		return (NULL);
	i = ft_vmin(2, n, ft_strlen(s));
	res = ft_calloc(sizeof(char), (i + 1));
	if (!res)
		return (NULL);
	ft_strlcpy(res, s, i + 1);
	return (res);
}

char	*strdup_until_sep(char *s, int nb_sep, ...)
{
	char	*res;
	va_list	seps;
	int		min;
	char	*tmp;

	if (!s)
		return (NULL);
	min = ft_strlen(s);
	tmp = NULL;
	va_start(seps, nb_sep);
	while (nb_sep--)
	{
		tmp = ft_strchr(s, va_arg(seps, int));
		if (tmp)
			min = ft_vmin(2, min, tmp - s);
	}
	va_end(seps);
	res = ft_calloc(sizeof(char), (min + 1));
	if (!res)
		return (NULL);
	ft_strlcpy(res, s, min + 1);
	return (res);
}

char	*strdup_until_funct(char *s, int (f(char c)))
{
	char	*res;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	while (f(s[i]))
		i += 1;
	res = ft_calloc(sizeof(char), (i + 1));
	if (!res)
		return (NULL);
	ft_strlcpy(res, s, i + 1);
	return (res);
}
