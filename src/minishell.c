/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basverdi <basverdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:38:06 by basverdi          #+#    #+#             */
/*   Updated: 2024/07/13 17:26:56 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "include/struct.h"
#include "include/utils.h"
#include <ctype.h>
#include <stdlib.h>
#include <sys/wait.h>

char	**ft_realloc_strs(char **str)
{
	int		i;
	char	**r;

	i = ft_str_str_len(str);
	if (!str)
		return (NULL);
	r = ft_calloc(sizeof(char *), (i + 2));
	if (!r)
	{
		ft_magic_free("%2", str);
		return (NULL);
	}
	i = 0;
	while (str[i])
	{
		r[i] = str[i];
		i++;
	}
	free(str);
	return (r);
}

int	in_child_cmd(char **cmd, t_lst_envp *envp, int fd[2])
{
	int		exit_status;
	int		p_id;
	char	**env;

	p_id = fork();
	if (p_id == 0)
	{
		dup2(fd[1], 1);
		ft_close(1, fd[1]);
		env = envp_to_char(envp);
		rl_clear_history();
		free_lst_envp(envp);
		execve(cmd[0], cmd, env);
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
	int		i;
	char	buf[11];
	int		fd[2];
	char	**str;

	i = 0;
	while (i < 10)
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

t_bool	correct_lang(t_lst_envp *envp)
{
	t_bool	return_value;
	char	**s;
	char	**tmp;
	char	*lang;

	return_value = 0;
	s = exec_child_cmd((char *[3]){"/bin/locale", "-a", (char *)0}, envp);
	lang = getenv("LANG");
	tmp = s;
	return_value = 0;
	while (return_value == 0 && s && *s)
	{
		return_value = !diff_lang(lang, *s);
		s++;
	}
	ft_free_split(tmp);
	return (return_value);
}

t_bool	no_emojy_rl(t_lst_envp *envp)
{
	t_bool	return_value;
	char	**s;
	char	*term_var;

	term_var = getenv("TERM");
	s = exec_child_cmd((char *[3]){"/bin/toe", "-a", (char *)0}, envp);
	return_value = (find_char_in_split(term_var, s) || correct_lang(envp));
	ft_free_split(s);
	return (!return_value);
}

int	ft_empty_line(char *line, t_lst_envp *lst_envp)
{
	if (line == NULL)
	{
		ft_printf_fd(2, "exit\n");
		free_lst_envp(lst_envp);
		return (0);
	}
	return (1);
}

t_bool	display_prompt(t_lst_envp *lst_envp)
{
	t_lst_cmd	*lst_line;
	char		*line;
	char		*prompt;
	int			no_color;

	prompt = NULL;
	no_color = 0;
	rl_outstream = stderr;
	while (1)
	{
		no_color = no_emojy_rl(lst_envp);
		set_sigaction(0);
		prompt = get_prompt(lst_envp, prompt, no_color);
		line = readline(prompt);
		ft_magic_free("%1", prompt);
		if (ft_empty_line(line, lst_envp) == 0)
			return (FALSE);
		if (*line)
			add_history(line);
		lst_line = parsing(line);
		exec(lst_line, &lst_envp);
	}
	return (TRUE);
}

int	main(int argc, char **argv, char **envp)
{
	t_lst_envp	*lst_envp;

	ft_clear_term(argc, argv);
	get_set_exit_code(0, TRUE);
	lst_envp = init_lst_envp(envp);
	if (display_prompt(lst_envp))
		free_lst_envp(lst_envp);
	rl_clear_history();
	return (get_set_exit_code(0, FALSE));
}
