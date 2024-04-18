/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basverdi <basverdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:38:06 by basverdi          #+#    #+#             */
/*   Updated: 2024/04/18 13:13:15 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exitcode;

void	ft_print_exit(char *str)
{
	ft_printf("%s", str);
	exit(42);
}

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
	if (ac == 2)
	{
		if (ft_strncmp(av[1], "--mini-coque", 12) == 0)
		{
			ft_printf("\u2B50 %s Bien joué! %s \u2B50\n", YELLOW, DEFAULT);
			ft_printf("Vous avez trouvé un des easters eggs !\n");
			ft_print_exit("PS : petite-coquille > bash\n");
		}
		else if (ft_strncmp(av[1], "--goat", 6) == 0)
			ft_print_exit("\u26A1 Made by Yroussea and Basverdi \u26A1\n");
		else if (ft_strncmp("--no-clear", av[1], 10))
			ft_printf("%sError%s\n%s", RED, DEFAULT, ERROR_ARGS);
	}
	else if (ac == 1 || ft_strncmp("--no-clear", av[1], 10))
		ft_printf("\033c");
	else if (ac > 1)
	{
		ft_printf("%sError%s\n%s", RED, DEFAULT, ERROR_ARGS);
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
		lst_line = exec(lst_line, lst_envp);
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
