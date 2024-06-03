/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unquoting.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basverdi <basverdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 12:06:03 by yroussea          #+#    #+#             */
/*   Updated: 2024/06/02 12:36:33 by yroussea         ###   ########.fr       */
/*                                                                            */
/* *******************************************************e******************* */

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

char	*ft_undoublequote(char *s, t_lst_envp *lst_envp)
{
	char	*res;
	char	*tmp;
	char	*tmp_str;

	res = strdup_until_sep(s, 2, 34, 36);
	while (s && *s && *s != 34 && *s != 36)
		s++;
	if (s && *s == 36)
	{
		tmp = ft_undolars(++s, lst_envp);
		s += skip_underscore(s);
		tmp_str = ft_undoublequote(s, lst_envp);
		return (join_and_free(3, "", res, tmp, tmp_str));
	}
	if (s && *s && *(s + 1))
	{
		tmp = ft_unquote(s + 1, lst_envp);
		return (join_and_free(2, "", res, tmp));
	}
	return (res);
}

char	*ft_undolars(char *s, t_lst_envp *lst_envp)
{
	char	*res;
	char	*variable;

	if (*s == '?')
		res = ft_strdup("?");
	else
		res = strdup_until_funct(s, is_alphanum_underscore);
	variable = get_envp_variable(lst_envp, res);
	if (res && !*res)
	{
		free(variable);
		variable = ft_strdup("$");
	}
	if (!variable)
	{
		free(res);
		return (ft_strdup(""));
	}
	free(res);
	return (variable);
}

char	*ft_unsimplequote(char *s, t_lst_envp *lst_envp)
{
	char	*res;
	char	*str;

	res = strdup_until_sep(s, 1, 39);
	while (s && *s && *s != 39)
		s++;
	str = ft_unquote(s + 1, lst_envp);
	return (join_and_free(2, "", res, str));
}

char	*ft_unquote(char *s, t_lst_envp *lst_envp)
{
	char	*res;
	char	*str;

	res = strdup_until_sep(s, 3, 34, 36, 39);
	while (s && *s && *s != 34 && *s != 36 && *s != 39)
		s++;
	if (s && *s == 34)
		return (join_and_free(2, "", res, ft_undoublequote(s + 1, lst_envp)));
	if (s && *s == 39)
		return (join_and_free(2, "", res, ft_unsimplequote(s + 1, lst_envp)));
	if (s && *s == 36)
	{
		str = ft_undolars(++s, lst_envp);
		if (str && !*str)
		{
			free(str);
			str = NULL;
		}
		s += skip_underscore(s);
		return (join_and_free(3, "", res, str, ft_unquote(s, lst_envp)));
	}
	return (res);
}
