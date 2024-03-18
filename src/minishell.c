/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basverdi <basverdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 17:06:41 by yroussea          #+#    #+#             */
/*   Updated: 2024/03/18 16:17:03 by basverdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(char *line, t_lst_envp	*lst_envp)
{
	if (ft_strncmp(line, "exit", 5) == 0 || ft_strncmp(line, "e", 5) == 0)
	{
		free(line);
		free_lst_envp(lst_envp);
		ft_printf("exit\n");
		return (0);
	}
	return (1);
}

int	ft_stop(int ac, char **av)
{
	if (ac == 2)
	{
		if (strncmp(av[1], "--mini-coque", 12) == 0)
		{
			ft_printf("\u2B50 %s Bien joué! %s \u2B50\n", YELLOW, DEFAULT);
			ft_printf("Vous avez trouvé un des easters eggs !\n");
			ft_printf("PS : petite-coquille > bash\n");
		}
		else if (strncmp(av[1], "--goat", 6) == 0)
			ft_printf("\u26A1 Made by Yroussea and Basverdi \u26A1\n");
		else
			ft_printf("%sError%s\n%s", RED, DEFAULT, ERROR_ARGS);
	}
	else
		ft_printf("%sError%s\n%s", RED, DEFAULT, ERROR_ARGS);
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
	while (1)
	{
		prompt = get_prompt(lst_envp, prompt);
		line = readline(prompt);
		ft_magic_free("%1 %1", prompt, user);
		if (line == NULL)
		{
			ft_printf("exit\n");
			break;
		}
		if (ft_exit(line, lst_envp) == 0)
			return (FALSE);
		lst_line = parsing(line);
		exec(lst_line);
	}
	return (TRUE);
}

int	main(int argc, char **argv, char **envp)
{
	t_lst_envp	*lst_envp;

	ft_printf("\033c");
	if (argc != 1)
		return (ft_stop(argc, argv));
	lst_envp = init_lst_envp(envp);
	set_sigaction(0);
	if (display_prompt(lst_envp) == FALSE)
		return (0);
	free_lst_envp(lst_envp);
}
