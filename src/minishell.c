/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 17:06:41 by yroussea          #+#    #+#             */
/*   Updated: 2024/03/12 16:43:17 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

int	main(int argc, char **argv, char **envp)
{
	t_lst_cmd	*lst_line;
	char		*line;
	t_lst_envp	*lst_envp;

	line = readline(">");
	lst_line = parsing(line);
	ft_print_lst(2, lst_line);
	free(line);
	lst_envp = init_lst_envp(envp);

	char	**en = envp_to_char(lst_envp);
	ft_printf("%S", en);
	free_lst_envp(lst_envp);

	(void)argc;
	(void)argv;
	(void)envp;
}
