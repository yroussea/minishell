/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastienverdier-vaissiere <bastienverdie    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 17:06:41 by yroussea          #+#    #+#             */
/*   Updated: 2024/03/12 23:36:25 by bastienverd      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
	t_lst_cmd *lst_line;
	char *line;
	t_lst_envp *lst_envp;
	char *prompt;

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
			break;
		if (ft_strncmp(line, "exit", 5) == 0)
		{
			free_lst_envp(lst_envp);
			free(line);
			return (0);
		}
		lst_line = parsing(line);
		ft_print_lst(2, lst_line);
		ft_lst_cmd_free(lst_line);
	}
	free_lst_envp(lst_envp);
	(void)argc;
	(void)argv;
	(void)envp;
}
