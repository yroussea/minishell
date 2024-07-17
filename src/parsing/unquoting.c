/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unquoting.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basverdi <basverdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 12:06:03 by yroussea          #+#    #+#             */
/*   Updated: 2024/07/17 14:12:03 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		tmp = ft_unquote(s + 1, lst, 0, NULL);
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

	str = NULL;
	res = strdup_until_sep(s, 1, 39);
	while (s && *s && *s != 39)
		s++;
	if (s && *s && *(s + 1))
		str = ft_unquote(s + 1, lst, in_dollar - in_dollar, NULL);
	return (join_and_free(2, "", res, str));
}

char	*invisible_char(t_bool creat, char *s)
{
	static char	*inv = "\001";

	if (creat == TRUE)
	{
		if (!ft_strchr(s, '\001'))
			inv = "\001";
		else if (!ft_strchr(s, '\002'))
			inv = "\002";
		else if (!ft_strchr(s, '\003'))
			inv = "\003";
		else if (!ft_strchr(s, '\004'))
			inv = "\004";
		else if (!ft_strchr(s, '\005'))
			inv = "\005";
		else if (!ft_strchr(s, '\006'))
			inv = "\006";
		else
			inv = "\001";
		return (NULL);
	}
	return (ft_strdup(inv));
}

char	*ft_unquote(char *s, t_lst_envp *lst, int in_dollar, char *res)
{
	char	*str;
	char	*tmp;

	res = strdup_until_sep(s, 3, 34, 36, 39);
	while (s && *s && *s != 34 && *s != 36 && *s != 39)
		s++;
	if (s && *s == 34)
		return (join_and_free(4, "", res, invisible_char(0, NULL), \
			ft_undoublequote(s + 1, lst, in_dollar), invisible_char(0, NULL)));
	if (s && *s == 39)
		return (join_and_free(4, "", res, invisible_char(0, NULL), \
			ft_unsimplequote(s + 1, lst, in_dollar), invisible_char(0, NULL)));
	if (s && *s == 36)
	{
		str = ft_undolars(++s, lst, in_dollar);
		s += skip_underscore(s);
		tmp = ft_unquote(s, lst, !!(in_dollar + *s == '"' || *s == '\''), 0);
		if (!str && (!res || !*res) && (!tmp || !*tmp))
		{
			ft_magic_free("%1 %1", res, tmp);
			return (NULL);
		}
		return (join_and_free(3, "", res, str, tmp));
	}
	return (res);
}
