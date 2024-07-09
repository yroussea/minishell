/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basverdi <basverdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:38:06 by basverdi          #+#    #+#             */
/*   Updated: 2024/07/09 09:16:14 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "include/utils.h"
#include <sys/wait.h>

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
	char		*user;

	prompt = NULL;
	user = NULL;
	rl_outstream = stderr;
	while (1)
	{
		set_sigaction(0);
		prompt = get_prompt(lst_envp, prompt);
		line = readline(prompt);
		ft_magic_free("%1 %1", prompt, user);
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
