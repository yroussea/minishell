/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unquoting.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basverdi <basverdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 12:06:03 by yroussea          #+#    #+#             */
/*   Updated: 2024/06/13 10:50:50 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdarg.h>

char	*join_and_free(size_t nb_str, char *sep, ...)
{
	va_list	args;
	va_list	copy;
	char	*s;

	va_start(args, sep);
	va_copy(copy, args);
	s = annex_vjoin(nb_str, sep, args);
	while (nb_str--)
		free(va_arg(copy, char *));
	va_end(copy);
	va_end(args);
	return (s);
}

char	*ft_undoublequote(char *s, t_lst_envp *lst, int in_dollar)
{
	char	*res;
	char	*tmp;
	char	*tmp_str;

	res = strdup_until_sep(s, 2, 34, 36);
	while (s && *s && *s != 34 && *s != 36)
		s++;
	if (s && *s == 36)
	{
		tmp = ft_undolars(++s, lst, in_dollar + 2);
		s += skip_underscore(s);
		tmp_str = ft_undoublequote(s, lst, in_dollar);
		if (!tmp)
			tmp = ft_strdup("");
		return (join_and_free(3, "", res, tmp, tmp_str));
	}
	if (s && *s && *(s + 1))
	{
		tmp = ft_unquote(s + 1, lst, 0);
		return (join_and_free(2, "", res, tmp));
	}
	return (res);
}

char	*ft_undolars(char *s, t_lst_envp *lst, int in_dollar)
{
	char	*res;
	char	*variable;

	if (*s == '?')
		res = ft_strdup("?");
	else
		res = strdup_until_funct(s, is_alphanum_underscore);
	variable = get_envp_variable(lst, res, 0);
	if (res && !*res)
	{
		free(variable);
		if ((*s == '\'' || *s == '"') && 0 == (in_dollar))
			variable = NULL;
		else
			variable = ft_strdup("$");
	}
	free(res);
	return (variable);
}

char	*ft_unsimplequote(char *s, t_lst_envp *lst, int in_dollar)
{
	char	*res;
	char	*str;

	res = strdup_until_sep(s, 1, 39);
	while (s && *s && *s != 39)
		s++;
	str = ft_unquote(s + 1, lst, in_dollar - in_dollar);
	return (join_and_free(2, "", res, str));
}

char	*ft_unquote(char *s, t_lst_envp *lst, int in_dollar)
{
	char	*res;
	char	*str;
	char	*tmp;

	res = strdup_until_sep(s, 3, 34, 36, 39);
	while (s && *s && *s != 34 && *s != 36 && *s != 39)
		s++;
	if (s && *s == 34)
		return (join_and_free(4, "", res, ft_strdup("\001"), \
			ft_undoublequote(s + 1, lst, in_dollar), ft_strdup("\001")));
	if (s && *s == 39)
		return (join_and_free(4, "", res, ft_strdup("\001"), \
			ft_unsimplequote(s + 1, lst, in_dollar), ft_strdup("\001")));
	if (s && *s == 36)
	{
		str = ft_undolars(++s, lst, in_dollar);
		s += skip_underscore(s); 
		tmp = ft_unquote(s, lst, !!(in_dollar + *s == '"' || *s == '\''));
		if (!str && (!res || !*res) && (!tmp || !*tmp))
		{
			ft_magic_free("%1 %1", res, tmp);
			return (NULL);
		}
		return (join_and_free(3, "", res, str, tmp));
	}
	return (res);
}
