/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokeniser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basverdi <basverdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 10:07:06 by yroussea          #+#    #+#             */
/*   Updated: 2024/03/15 12:46:08 by basverdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stdarg.h>

int	is_token(char *s, char **token)
{
	while (token && *token)
	{
		if (ft_strncmp(s, *token, ft_strlen(*token)) == 0)
			return (ft_strlen(*token));
		token += 1;
	}
	return (FALSE);
}

static size_t	ft_count_word(char *s, char **token)
{
	size_t	count;
	int		tmp;

	count = 0;
	while (s && *s)
	{
		tmp = is_token(s, token);
		if (tmp)
		{
			count += 1;
			s += tmp;
		}
		else
			s += 1;
	}
	return (2 * count + 1);
}

static size_t	len_next_word(char *s, char **token, size_t len)
{
	size_t	j;
	size_t	min;
	char	*tmp;

	min = len;
	j = is_token(s, token);
	if  (j)
		return (j);
	while (token && *token)
	{
		tmp = ft_strnstr(s, *token, len);
		if (tmp)
		{
			j = tmp - s;
			if (j < min)
			{
				min = j;
			}
		}
		token += 1;
	}
	return (min);
}

char	**ft_tokeniser(char *s, char **token)
{
	char	**result;
	size_t	j;
	size_t	k;

	k = 0;
	result = ft_calloc(sizeof(char *), ft_count_word(s, token) + 1);
	if  (!result)
		return (NULL);
	while (s && *s)
	{
		j = len_next_word(s, token, ft_strlen(s));
		result[k] = ft_calloc(sizeof(char *), (j + 1));
		if (!result[k])
		{
			ft_magic_free("%2", result);
			return (NULL);
		}
		ft_strlcpy(result[k], s, j + 1);
		s += j;
		k += 1;
	}
	return (result);
}

char	**va_tokeniser(char *s, int nb, ...)
{
	char	**token;
	char	**result;
	va_list	args;
	int		i;

	i = 0;
	token = ft_calloc((nb + 1), sizeof(char *));
	va_start(args, nb);
	while (token && i < nb)
	{
		token[i] = ft_strdup(va_arg(args, char *));
		if (!token[i])
		{
			ft_magic_free("%2", token);
			return (NULL);
		}
		i += 1;
	}
	va_end(args);
	if (s && token)
		result = ft_tokeniser(s, token);
	else
		result = NULL;
	ft_magic_free("%2", token);
	return (result);
}
