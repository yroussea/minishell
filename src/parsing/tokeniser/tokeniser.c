/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokeniser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basverdi <basverdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 10:07:06 by yroussea          #+#    #+#             */
/*   Updated: 2024/07/17 14:26:44 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stdarg.h>

size_t	jump_quote(char *s, size_t len, size_t *count)
{
	size_t	tmp;

	if (*s == 34 && *(s + 1))
	{
		tmp = len_quote(s + 1, DOUBLE) + 2;
		if (len < tmp)
		{
			*count += 2;
			tmp = len;
		}
		return (tmp);
	}
	if (*s == 39 && *(s + 1))
	{
		tmp = len_quote(s + 1, SIMPLE) + 2;
		if (len < tmp)
		{
			*count += 2;
			tmp = len;
		}
		return (tmp);
	}
	*count += 1;
	return (*s == 34 || *s == 39);
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

void	conc_good_token(char *r, char *s, int j)
{
	if (j == -1)
		ft_strlcpy(r, " ", 2);
	else
		ft_strlcpy(r, s, j + 1);
}

char	**ft_tokeniser(char *s, char **token)
{
	char	**result;
	int		j;
	size_t	k;

	k = 0;
	result = ft_calloc(sizeof(char *), ft_count_word(s, token, 0) * 2);
	while (result && s && *s)
	{
		j = is_token(s, token);
		if (j && ft_iswhitespace(*s))
			j = -1;
		if (!j)
			j = len_next_word(s, token, ft_strlen(s));
		result[k] = ft_calloc(sizeof(char *), (ft_abs(j) + 1));
		if (!result[k])
		{
			ft_magic_free("%2", result);
			return (NULL);
		}
		conc_good_token(result[k++], s, j);
		s += ft_abs(j);
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
