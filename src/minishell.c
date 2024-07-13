/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basverdi <basverdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:38:06 by basverdi          #+#    #+#             */
/*   Updated: 2024/07/13 07:40:36 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "include/struct.h"
#include "include/utils.h"
#include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

#define BUFFER 10000 //si buff < taille?
char	**exec_child_cmd(char **cmd, t_lst_envp *envp)
{
	int	fd[2];
	int	exit_status;
	int	p_id;

	pipe(fd);
	p_id = fork();
	if (p_id == 0)
	{
		dup2(fd[1], 1);
		ft_close(2, fd[0], fd[1]);
		char	**env = envp_to_char(envp);
		rl_clear_history();
		free_lst_envp(envp);
		execve(cmd[0], cmd, env);
		ft_free_split(env);
		exit(1);
	}
	waitpid(p_id, &exit_status, 0);
	if (WEXITSTATUS(exit_status))
		exit(1); //pas un exit
	char	*s=malloc(BUFFER);
	int r = BUFFER;
	r = read(fd[0], s, BUFFER);
	if (r <= 0)
		return (NULL);
	s[r] = 0;
	ft_close(2, fd[0], fd[1]);
	char	**str = ft_split(s, '\n');
	free(s);
	return (str);
}

char	*get_var_char(char *key)
{
	return (getenv(key));
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

t_bool	correct_lang(t_lst_envp *envp)
{
	t_bool	return_value = 0;
	char	**s1 = exec_child_cmd((char *[3]){"/bin/locale", "-a", (char *)0}, envp);
	char	*lang = get_var_char("LANG");
	char	*x = NULL;

	if (lang)
		x = ft_strnstr(lang, "UTF", ft_strlen(lang) + 1);
	if (lang && x)
	{
		x[0] = 'u';
		x[1] = 't';
		x[2] = 'f';
	}
	return_value = find_char_in_split(lang, s1);
	ft_free_split(s1);
	return (return_value);
}

t_bool no_emojy_rl(t_lst_envp *envp)
{
	t_bool	return_value = 0;
	char	**s2 = exec_child_cmd((char *[3]){"/bin/toe", "-a", (char *)0}, envp);
	char	*term_var = get_var_char("TERM");
	if (correct_lang(envp) || find_char_in_split(term_var, s2))
		return_value = 1;
	ft_free_split(s2);
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
