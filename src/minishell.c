/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basverdi <basverdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:38:06 by basverdi          #+#    #+#             */
/*   Updated: 2024/06/09 06:52:21 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "include/utils.h"
#include <sys/wait.h>

int	g_exitcode;

int	ft_empty_line(char *line, t_lst_envp *lst_envp)
{
	if (line == NULL)
	{
		ft_printf("exit\n");
		free_lst_envp(lst_envp);
		return (0);
	}
	return (1);
}

void	ft_stop(int ac, char **av)
{
	if (ac > 1 && ft_strncmp("--no-clear", av[1], 10))
	{
		if (!ft_strncmp(av[1], "--mini-coque", 12))
			ft_printf_fd(2, WELL_PLAYED, YELLOW, DEFAULT, EASTER_EGG, \
				BETTER_THAN_BASH);
		else if (!ft_strncmp(av[1], "--goat", 6))
			ft_printf_fd(2, AUTOR);
		else if (!ft_strncmp(av[1], "--42sh", 6))
			ft_printf_fd(2, MINISHORSH);
		else
			ft_printf_fd(2, "%sError%s\n%s", RED, DEFAULT, ERROR_ARGS);
		exit(42);
	}
	else if (ac == 1 || ft_strncmp("--no-clear", av[1], 10))
		ft_printf_fd(2, "\033c");
	else if (ac > 2)
	{
		ft_printf_fd(2, "%sError%s\n%s", RED, DEFAULT, ERROR_ARGS);
		exit(1);
	}
}

t_bool	display_prompt(t_lst_envp *lst_envp)
{
	t_lst_cmd	*lst_line;
	char		*line;
	char		*prompt;
	char		*user;

	prompt = NULL;
	user = NULL;
	// rl_outstream = stderr;
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

	ft_stop(argc, argv);
	g_exitcode = 0;
	lst_envp = init_lst_envp(envp);
	if (display_prompt(lst_envp) == FALSE)
	{
		clear_history();
		return (0);
	}
	free_lst_envp(lst_envp);
	clear_history();
}
