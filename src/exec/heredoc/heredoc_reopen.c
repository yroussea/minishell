/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_reopen.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basverdi <basverdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 12:57:07 by yroussea          #+#    #+#             */
/*   Updated: 2024/04/13 15:08:02 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_undolars_heredoc(char *s, t_lst_envp *lst_envp)
{
	char	*res;
	char	*variable;

	res = strdup_until_sep(s, 5, 34, 36, 39, ' ', '\n'); //every non-alphanum caractere
	variable = get_envp_variable(lst_envp, res);
	free(res);
	return (variable);
}

char	ft_random(void)
{
	char	buf[1];
	int		fd;

	fd = open("/dev/random", 0);
	read(fd, buf, 1);
	ft_close(1, fd);
	return (97 + ft_abs(*buf % 26));
}

char	*replace_dollar(char *s, t_lst_envp *lst_envp)
{
	char	*result;
	char	*str;
	char	*tmp;
	char	*tmp_str;

	result = strdup_until_sep(s, 1, 36);
	while (s && *s && *s != 36)
		s++;
	if (s && *s == 36)
	{
		str = ft_undolars_heredoc(++s, lst_envp);
		while (s && *s && *s != 34 && *s != 36 && \
			*s != 39 && *s != ' ' && *s != '\n')  //every non-alpha-num cara
			s++;
		tmp_str = replace_dollar(s, lst_envp);
		tmp = ft_vjoin(3, "", result, str, tmp_str);
		ft_magic_free("%1 %1 %1", result, str, tmp_str);
		return (tmp);
	}
	return (result);
}

t_bool	fill_heredoc(int old_fd, int new_fd, t_lst_envp *lst_envp)
{
	char	*buf;
	char	*str;
	int		r;

	r = 1;
	str = NULL;
	while (r)
	{
		buf = malloc(100 + 1);
		r = read(old_fd, buf, 100);
		if (r == -1)
		{
			free(str);
			free(buf);
			return (FALSE);
		}
		buf[r] = 0;
		str = ft_vjoin(2, "", str, buf);
		free(buf);
	}
	buf = replace_dollar(str, lst_envp);
	free(str);
	ft_printf_fd(new_fd, "%s", buf);
	return (TRUE);
}

int	heredoc_reopen(int fd, t_lst_envp *lst_envp)
{
	int		new_fd;
	char	buf[19];
	int		i;

	ft_strlcpy(buf, ".heredoc", 9);
	i = 8;
	while (i < 18)
		buf[i++] = ft_random();
	buf[i] = 0;
	new_fd = open((char *)buf, 577, 0664);
	if (!fill_heredoc(fd, new_fd, lst_envp))
	{
		unlink(buf);
		close(!new_fd);
		return (fd);
	}
	close(fd);
	close(new_fd);
	new_fd = open((char *)buf, 0);
	unlink(buf);
	return (new_fd);
}
