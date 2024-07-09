/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basverdi <basverdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 17:26:55 by basverdi          #+#    #+#             */
/*   Updated: 2024/07/09 09:16:14 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

size_t	ft_count_word(char *s, char **token, size_t count)
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

size_t	len_next_token(char *s, char **token, size_t len)
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

size_t	len_next_word(char *s, char **token, size_t len)
{
	size_t	j;
	size_t	quote;
	size_t	min;

	if (!s || !*s)
		return (0);
	j = is_token(s, token);
	if (j)
		return (0);
	min = len_next_token(s, token, len);
	quote = ft_vmin(2, len_quote(s, DOUBLE), len_quote(s, SIMPLE));
	if (quote == 0)
	{
		if (*s == 34)
			quote = ft_vmin(2, len_quote(s + 1, DOUBLE) + 2, len);
		if (*s == 39)
			quote = ft_vmin(2, len_quote(s + 1, SIMPLE) + 2, len);
		return (quote + len_next_word(s + quote, token, len - quote));
	}
	if (quote < min)
		return (quote + len_next_word(s + quote, token, len - quote));
	return (min);
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

int	skip_underscore(char *s)
{
	char	*tmp;

	tmp = s;
	if (!s)
		return (0);
	if (*s == '?')
		return (1);
	while (*s && (ft_isalnum(*s) || *s == '_'))
		s++;
	return (s - tmp);
}
