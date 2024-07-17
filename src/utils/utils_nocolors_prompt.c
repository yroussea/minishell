/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_nocolors_prompt.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basverdi <basverdi@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 17:37:16 by basverdi          #+#    #+#             */
/*   Updated: 2024/07/17 14:21:20 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_bool	diff_lang(char *lang, char *cmp)
{
	while (lang && cmp && (*lang || *cmp))
	{
		if (*lang && !ft_isalnum(*lang))
		{
			lang++;
			continue ;
		}
		if (*cmp && !ft_isalnum(*cmp))
		{
			cmp++;
			continue ;
		}
		if (*cmp && *lang && ft_tolower(*cmp) == ft_tolower(*lang))
		{
			cmp++;
			lang++;
			continue ;
		}
		break ;
	}
	return (*cmp || *lang);
}

int	in_child_cmd(char **cmd, t_lst_envp *envp, int fd[2])
{
	int		exit_status;
	int		p_id;
	char	**env;

	p_id = fork();
	if (p_id == 0)
	{
		rl_clear_history();
		env = envp_to_char(envp);
		free_lst_envp(envp);
		if (dup2(fd[1], 1) != -1)
		{
			ft_close(1, fd[1]);
			execve(cmd[0], cmd, env);
		}
		ft_free_split(env);
		exit(1);
	}
	waitpid(p_id, &exit_status, 0);
	return (WEXITSTATUS(exit_status));
}

char	**gnl_all_file(char *file, int *fd)
{
	char	**str;
	int		i;

	i = 0;
	*fd = open(file, O_RDONLY);
	str = ft_calloc(sizeof(char *), 2);
	while (str)
	{
		str[i] = get_next_line(*fd);
		if (!str[i++])
			break ;
		str = ft_realloc_strs(str);
	}
	if (str)
		str[i] = NULL;
	return (str);
}

char	**exec_child_cmd(char **cmd, t_lst_envp *envp)
{
	int			i;
	static char	buf[16] = "/tmp/";
	int			fd[2];
	char		**str;

	i = 5;
	while (i < 15)
		buf[i++] = ft_random();
	buf[i] = 0;
	fd[1] = open(buf, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (!fd[1])
		return (NULL);
	if (in_child_cmd(cmd, envp, fd))
	{
		ft_close(1, fd[1]);
		unlink(buf);
		return (NULL);
	}
	str = gnl_all_file(buf, fd);
	ft_close(2, fd[0], fd[1]);
	unlink(buf);
	return (str);
}

t_bool	find_char_in_split(char *s, char **spl)
{
	uint	len;

	len = ft_strlen(s);
	while (s && spl && *spl)
	{
		if (!ft_strncmp(s, *spl, len))
			return (TRUE);
		spl++;
	}
	return (FALSE);
}
