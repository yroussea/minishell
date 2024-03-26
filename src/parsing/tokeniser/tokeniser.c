/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokeniser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basverdi <basverdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 10:07:06 by yroussea          #+#    #+#             */
/*   Updated: 2024/03/26 16:32:40 by yroussea         ###   ########.fr       */
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

size_t	jump_quote(char *s, size_t len, size_t *count)
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

size_t	jump_token(char *s, char **token, size_t *count, t_bool *bool)
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
		j = is_token(s, token);
		if (!j)
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
