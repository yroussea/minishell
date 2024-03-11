/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 17:06:41 by yroussea          #+#    #+#             */
/*   Updated: 2024/03/11 19:34:47 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_lst_cmd	*lst_line;
	char		*line;

	line = readline(">");
	lst_line = parsing(line);
	ft_print_lst(2, lst_line);
	(void)argc;
	(void)argv;
	(void)envp;
}
