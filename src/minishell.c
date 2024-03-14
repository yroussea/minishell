/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basverdi <basverdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 17:06:41 by yroussea          #+#    #+#             */
/*   Updated: 2024/03/14 19:58:02 by basverdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(char *line, t_lst_envp	*lst_envp)
{
	if (ft_strncmp(line, "exit", 5) == 0 || ft_strncmp(line, "e", 5) == 0)
	{
		free(line);
		free_lst_envp(lst_envp);
		return (0);
	}
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	t_lst_cmd	*lst_line;
	char		*line;
	t_lst_envp	*lst_envp;
	char		*prompt;

	if (argc != 1)
		return (1);
	lst_envp = init_lst_envp(envp);
	prompt = NULL;
	while (1)
	{
		prompt = get_prompt(lst_envp, prompt);
		line = readline(prompt);
		free(prompt);
		if (line == NULL)
			break ;
		if (ft_exit(line, lst_envp) == 0)
			return (0);
		lst_line = parsing(line);
		ft_print_lst(2, lst_line);
		ft_lst_cmd_free(lst_line);
	}
	free_lst_envp(lst_envp);
	(void)argv;
}
