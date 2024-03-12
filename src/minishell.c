/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basverdi <basverdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 17:06:41 by yroussea          #+#    #+#             */
/*   Updated: 2024/03/12 21:05:11 by basverdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "function.h"

int	main(int argc, char **argv, char **envp)
{
	t_lst_cmd	*lst_line;
	char		*line;
	t_lst_envp	*lst_envp;
	char		*prompt;

	if (argc != 1)
		return (1);
	lst_envp = init_lst_envp(envp);
	prompt = get_prompt(lst_envp);

	while (1)
	{
		line = readline(prompt);
		if (line == NULL)
			break;
		if (ft_strncmp(line, "exit", 5) == 0)
		{
			free(prompt);
			free_lst_envp(lst_envp);
			free(line);
			return (0);
		}
		lst_line = parsing(line);
		ft_print_lst(2, lst_line);
		ft_lst_cmd_free(lst_line);
	}
	free(prompt);
	free_lst_envp(lst_envp);
	(void)argc;
	(void)argv;
	(void)envp;
}
