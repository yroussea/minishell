/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unquoting.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 12:06:03 by yroussea          #+#    #+#             */
/*   Updated: 2024/03/25 15:00:18 by yroussea         ###   ########.fr       */
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
	res = malloc(sizeof(char) * (min + 1));
	if (!res)
		return (NULL);
	ft_strlcpy(res, s, min + 1);
	va_end(seps);
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

	res = strdup_until_sep(s, 2, 34, 36);
	while (s && *s && *s != 34 && *s != 36)
		s++;
	if (*s == 36)
	{
		tmp = ft_undolars(++s, lst_envp);
		while (s && *s && *s != 34 && *s != 36 && *s != 39)
			s++;
		return (ft_vjoin(3, "", res, tmp, ft_undoublequote(s, lst_envp)));
	}
	if (s && *s && *(s + 1))
		return (ft_vjoin(2, "", res, ft_unquote(s + 1, lst_envp)));
	return (res);
}

char	*ft_undolars(char *s, t_lst_envp *lst_envp)
{
	char	*res;
	char	*variable;

	res = strdup_until_sep(s, 3, 34, 36, 39);
	variable = get_envp_variable(lst_envp, res);
	free(res);
	return (variable);
}

char	*ft_unsimplequote(char *s, t_lst_envp *lst_envp)
{
	char	*res;

	res = strdup_until_sep(s, 1, 39);
	while (s && *s && *s != 39)
		s++;
	return (ft_vjoin(2, "", res, ft_unquote(s + 1, lst_envp)));
}

char	*ft_unquote(char *s, t_lst_envp *lst_envp)
{
	char	*res;

	res = strdup_until_sep(s, 3, 34, 36, 39);
	while (s && *s && *s != 34 && *s != 36 && *s != 39)
		s++;
	ft_printf_fd(2, "#A->%s--%s\n",s,res);
	if (s && *s == 34)
		return (ft_vjoin(2, "", res, ft_undoublequote(s + 1, lst_envp)));
	if (s && *s == 36)
		return (ft_vjoin(2, "", res, ft_undolars(s + 1, lst_envp)));
	if (s && *s == 39)
		return (ft_vjoin(2, "", res, ft_unsimplequote(s + 1, lst_envp)));
	return (res);
}
