/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basverdi <basverdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:38:06 by basverdi          #+#    #+#             */
/*   Updated: 2024/07/17 14:23:04 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "include/struct.h"
#include "include/utils.h"
#include <stdlib.h>
#include <sys/wait.h>

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

#ifndef FAST_PROMPT

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

#else

t_bool	no_emojy_rl(t_lst_envp *envp)
{
	static t_bool	return_value = -1;
	char			**s;
	char			*term_var;

	if (return_value != -1)
		return (!return_value);
	term_var = getenv("TERM");
	s = exec_child_cmd((char *[3]){"/bin/toe", "-a", (char *)0}, envp);
	return_value = (find_char_in_split(term_var, s) || correct_lang(envp));
	ft_free_split(s);
	return (!return_value);
}

#endif

t_bool	display_prompt(t_lst_envp *lst_envp)
{
	t_lst_cmd	*lst_line;
	char		*line;
	char		*prompt;
	static int	no_color = 0;

	prompt = NULL;
	while (1)
	{
		set_sigaction(0);
		no_color = no_emojy_rl(lst_envp);
		prompt = get_prompt(lst_envp, prompt, no_color);
		line = readline(prompt);
		ft_magic_free("%1", prompt);
		if (line == NULL)
		{
			ft_printf_fd(2, "exit\n");
			free_lst_envp(lst_envp);
			return (FALSE);
		}
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
	rl_outstream = stderr;
	if (display_prompt(lst_envp))
		free_lst_envp(lst_envp);
	rl_clear_history();
	return (get_set_exit_code(0, FALSE));
}
