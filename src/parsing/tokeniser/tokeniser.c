/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokeniser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 10:07:06 by yroussea          #+#    #+#             */
/*   Updated: 2024/03/15 18:04:46 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stdarg.h>
static size_t	len_quote(char *s, t_quote quote);

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
	t_bool	was_token;

	count = 0;
	was_token = TRUE;
	while (s && *s)
	{
		tmp = is_token(s, token);
		if (tmp)
		{
			count += 1;
			s += tmp;
			was_token = TRUE;
		}
		else if (*s == 34 && *(s + 1))
			s += len_quote(s + 1, DOUBLE) + 2;
		else if (*s == 39 && (s + 1))
			s += len_quote(s + 1, SIMPLE) + 2;
		else if (*s == 34 || *s == 39)
			s += 1;
		else
		{
			if (was_token == TRUE)
				count += 1;
			was_token = FALSE;
			s += 1;
		}
	}
	return (count);
}

static size_t	len_quote(char *s, t_quote quote)
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

static size_t	len_next_word(char *s, char **token, char **tk_save, size_t len)
{
	size_t	j;
	size_t	min;
	char	*tmp;
	size_t	next_quote;

	if (!s || !*s)
		return (0);
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
			min = ft_vmin(2, min, j);
		}
		token += 1;
	}
	next_quote = ft_vmin(2, len_quote(s, DOUBLE), len_quote(s, SIMPLE));
	if (next_quote == 0)
	{
		next_quote = ft_vmin(2, len_quote(s + 1, DOUBLE), len_quote(s + 1, SIMPLE)) + 2;
		return (next_quote + len_next_word(s + next_quote, tk_save, tk_save, len - next_quote));
	}
	if (next_quote < min)
		return (next_quote + len_next_word(s + next_quote, tk_save, tk_save, len - next_quote));
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
		j = len_next_word(s, token, token, ft_strlen(s));
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
