/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 17:06:41 by yroussea          #+#    #+#             */
/*   Updated: 2024/03/12 17:39:35 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "function.h"

int	main(int argc, char **argv, char **envp)
{
	t_lst_cmd	*lst_line;
	char		*line;
	t_lst_envp	*lst_envp;

	if (argc != 1)
		return (1);
	lst_envp = init_lst_envp(envp);
	//ft_printf("%S", get_all_path(lst_envp));

	while (1)
	{
		line = readline(get_envp_variable(lst_envp, "PWD"));
		lst_line = parsing(line);
		ft_print_lst(2, lst_line);
		free(line);
	}

	free_lst_envp(lst_envp);
	(void)argc;
	(void)argv;
	(void)envp;
}
