/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basverdi <basverdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 13:28:50 by basverdi          #+#    #+#             */
/*   Updated: 2024/06/09 07:07:07 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

extern int	g_exitcode;

void	ft_cd(t_node *node)
{
	char	buf[10000];
	char	*var;

	if (ft_str_str_len(node->args) > 2)
	{
		g_exitcode = 1;
		ft_printf_fd(node->errorfile, "petite-coquille: cd: too many arguments\n");
		return ;
	}
	getcwd(buf, 10000);
	var = ft_vjoin(2, "", "OLDPWD=", buf);
	ft_export(node, var);
	free(var);
	if (ft_str_str_len(node->args) < 1)
		chdir("~/");
	else
		chdir(node->args[1]);
	getcwd(buf, 10000);
	var = ft_vjoin(2, "", "PWD=", buf);
	ft_export(node, var);
	free(var);
	g_exitcode = errno;
	if (g_exitcode != 0)
	{
		g_exitcode = 1;
		ft_printf_fd(node->errorfile, \
			"petite-coquille: cd: %s: No such file or directory\n", \
			node->args[1]);
	}
}
