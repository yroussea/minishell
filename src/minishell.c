/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 17:06:41 by yroussea          #+#    #+#             */
/*   Updated: 2024/03/12 15:13:00 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

	t_lst_envp *tmp = lst_envp;
	while (lst_envp)
	{
		ft_printf("%s = %s\n", lst_envp->key, lst_envp->value);
		lst_envp = lst_envp->next;
	}
	free_lst_envp(tmp);

	(void)argc;
	(void)argv;
	(void)envp;
}
