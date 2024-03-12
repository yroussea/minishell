/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 17:06:41 by yroussea          #+#    #+#             */
/*   Updated: 2024/03/12 17:28:21 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_lst_cmd	*lst_line;
	char		*line;
	t_lst_envp	*lst_envp;

	if (argc != 1)
		return (1);
	lst_envp = init_lst_envp(envp);
	char	**en = envp_to_char(lst_envp);
	ft_printf("%S", en);
	free_lst_envp(lst_envp);

	while (1)
	{
		line = readline(">");
		lst_line = parsing(line);
		ft_print_lst(2, lst_line);
		free(line);
	}

	(void)argc;
	(void)argv;
	(void)envp;
}
