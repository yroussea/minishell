/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokeniser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 10:07:06 by yroussea          #+#    #+#             */
/*   Updated: 2024/03/15 22:50:34 by yroussea         ###   ########.fr       */
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

static size_t	jump_quote(char *s, size_t len, size_t *count)
{
	size_t	tmp;

	if (*s == 34 && *(s + 1))
	{
		tmp = len_quote(s + 1, DOUBLE) + 2;
		if (len < tmp)
		{
			*count += 1;
			tmp = len;
		}
		return (tmp);
	}
	if (*s == 39 && *(s + 1))
	{
		tmp = len_quote(s + 1, SIMPLE) + 2;
		if (len < tmp)
		{
			*count += 1;
			tmp = len;
		}
		return (tmp);
	}
	else if (*s == 34 || *s == 39)
		return (1);
	return (0);
}

static size_t	jump_token(char *s, char **token, size_t *count, t_bool *bool)
{
	int	tmp;

	tmp = is_token(s, token);
	if (tmp)
	{
		*count += 1;
		*bool = TRUE;
	}
	return (tmp);
}

static size_t	ft_count_word(char *s, char **token, size_t count)
{
	int		tmp;
	t_bool	was_token;

	was_token = TRUE;
	while (s && *s)
	{
		tmp = jump_token(s, token, &count, &was_token);
		if (tmp)
			s += tmp;
		if (tmp)
			continue ;
		tmp = jump_quote(s, ft_strlen(s), &count);
		s += tmp;
		if (!tmp)
		{
			count += was_token;
			was_token = FALSE;
			s += 1 - tmp;
		}
	}
	if (s && !*s && (*(s - 1) == 34 || *(s - 1) == 39))
		count += 1;
	return (count);
}

size_t	len_quote(char *s, t_quote quote)
{
	char	*tmp;

	tmp = s;
	while (tmp && *tmp)
	{
		if (*tmp == 39 && quote == SIMPLE) 
			break ;
		if (*tmp == 34 && quote == DOUBLE) 
			break ;
		tmp += 1;
	}
	return (tmp - s);
}

static size_t	len_next_token(char *s, char **token, size_t len)
{
	size_t	min;
	char	*tmp;
	size_t	j;

	min = len;
	while (token && *token)
	{
		tmp = ft_strnstr(s, *token, len);
		if (tmp)
		{
			j = tmp - s;
			min = ft_vmin(2, min, j);
		}
		token += 1;
	}
	return (min);
}

static size_t	len_next_word(char *s, char **token, size_t len)
{
	size_t	j;
	size_t	quote;
	size_t	min;

	if (!s || !*s)
		return (0);
	j = is_token(s, token);
	if (j)
		return (j);
	min = len_next_token(s, token, len);
	quote = ft_vmin(2, len_quote(s, DOUBLE), len_quote(s, SIMPLE));
	if (quote == 0)
	{
		quote = ft_vmin(3, len_quote(s + 1, DOUBLE), \
					len_quote(s + 1, SIMPLE), len - 2) + 2;
		return (quote + len_next_word(s + quote, token, len - quote));
	}
	if (quote < min)
		return (quote + len_next_word(s + quote, token, len - quote));
	return (min);
}

char	**ft_tokeniser(char *s, char **token)
{
	char	**result;
	size_t	j;
	size_t	k;

	k = 0;
	result = ft_calloc(sizeof(char *), ft_count_word(s, token, 0) + 1);
	if (!result)
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
	if (s && *s && token)
		result = ft_tokeniser(s, token);
	else
		result = NULL;
	ft_magic_free("%2", token);
	return (result);
}
