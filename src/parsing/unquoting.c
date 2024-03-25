/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unquoting.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 12:06:03 by yroussea          #+#    #+#             */
/*   Updated: 2024/03/25 17:40:15 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdarg.h>

char	*strdup_until_sep(char *s, int nb_sep, ...)
{
	char	*res;
	va_list	seps;
	int		i;
	int		min;
	char	*tmp;

	if (!s)
		return (NULL);
	i = 0;
	min = ft_strlen(s);
	va_start(seps, nb_sep);
	tmp = NULL;
	while (i < nb_sep)
	{
		int	x = va_arg(seps, int);
		tmp = ft_strchr(s, x);
		if (tmp)
			min = ft_vmin(2, min, tmp - s);
		i++;
	}
	va_end(seps);
	res = ft_calloc(sizeof(char), (min + 1));
	if (!res)
		return (NULL);
	ft_strlcpy(res, s, min + 1);
	return (res);
}

/*
* 34 = "
* 36 = $
* 39 = '
*/
char	*ft_unsimplequote(char *s, t_lst_envp *lst_envp);
char	*ft_undolars(char *s, t_lst_envp *lst_envp);
char	*ft_undoublequote(char *s, t_lst_envp *lst_envp);
char	*ft_unquote(char *s, t_lst_envp *lst_envp);

char	*ft_undoublequote(char *s, t_lst_envp *lst_envp)
{
	char	*res;
	char	*tmp;
	char	*str;
	char	*tmp_str;

	res = strdup_until_sep(s, 2, 34, 36);
	while (s && *s && *s != 34 && *s != 36)
		s++;
	if (s && *s == 36)
	{
		tmp = ft_undolars(++s, lst_envp);
		while (s && *s && *s != 34 && *s != 36 && *s != 39 && *s != ' ')
			s++;
		tmp_str = ft_undoublequote(s, lst_envp);
		str = ft_vjoin(3, "", res, tmp, tmp_str);
		ft_magic_free("%1 %1 %1", res, tmp, tmp_str);
		return (str);
	}
	if (s && *s && *(s + 1))
	{
		tmp = ft_unquote(s + 1, lst_envp);
		str = ft_vjoin(2, "", res, tmp);
		ft_magic_free("%1 %1", res, tmp);
		return (str);
	}
	return (res);
}

char	*ft_undolars(char *s, t_lst_envp *lst_envp)
{
	char	*res;
	char	*variable;

	res = strdup_until_sep(s, 4, 34, 36, 39, ' ');
	variable = get_envp_variable(lst_envp, res);
	free(res);
	return (variable);
}

char	*ft_unsimplequote(char *s, t_lst_envp *lst_envp)
{
	char	*res;
	char	*tmp;
	char	*str;

	res = strdup_until_sep(s, 1, 39);
	while (s && *s && *s != 39)
		s++;
	str = ft_unquote(s + 1, lst_envp);
	tmp = ft_vjoin(2, "", res, str);
	ft_magic_free("%1 %1", str, res);
	return (tmp);
}

char	*ft_unquote(char *s, t_lst_envp *lst_envp)
{
	char	*res;
	char	*tmp;
	char	*str;

	res = strdup_until_sep(s, 3, 34, 36, 39);
	while (s && *s && *s != 34 && *s != 36 && *s != 39)
		s++;
	if (s && *s == 34)
	{
		str = ft_undoublequote(s + 1, lst_envp);
		tmp = ft_vjoin(2, "", res, str);
		ft_magic_free("%1 %1", str, res);
		return (tmp);
	}
	if (s && *s == 36)
	{
		str = ft_undolars(s + 1, lst_envp);
		tmp = ft_vjoin(2, "", res, str);
		ft_magic_free("%1 %1", str, res);
		return (tmp);
	}
	if (s && *s == 39)
	{
		str = ft_unsimplequote(s + 1, lst_envp);
		tmp = ft_vjoin(2, "", res, str);
		ft_magic_free("%1 %1", str, res);
		return (tmp);
	}
	return (res);
}
