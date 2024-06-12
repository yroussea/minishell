/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basverdi <basverdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 13:28:50 by basverdi          #+#    #+#             */
/*   Updated: 2024/06/12 17:14:13 by basverdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

extern int	g_exitcode;

t_bool	go_to_oldpwd(t_node *node)
{
	char	*var;
	
	if (ft_strncmp(node->args[1], "-", 1) == 0)
	{
		var = get_envp_variable(*node->envp, "OLDPWD");
		if (var)
		{
			node->args[1] = var;
			ft_cd(node);
			return (TRUE);
		}
		else
		{
			g_exitcode = 1;
			ft_printf_fd(node->errorfile, "petite-coquille: cd: OLDPWD not set\n");
			return (FALSE);
		}
	}
	return (FALSE);
}

t_bool	cd_err(t_node *node)
{
	if (ft_str_str_len(node->args) > 2)
	{
		g_exitcode = 1;
		ft_printf_fd(node->errorfile, "petite-coquille: cd: too many arguments\n");
		return (TRUE);
	}
	if (g_exitcode != 0)
	{
		g_exitcode = 1;
		ft_printf_fd(node->errorfile, \
			"petite-coquille: cd: %s: No such file or directory\n", \
			node->args[1]);
	}
	return (FALSE);
}

void	ft_cd(t_node *node)
{
	char	buf[10000];
	char	*var;

	if (cd_err(node))
		return ;
	if (go_to_oldpwd(node))
		return ;
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
	cd_err(node);
}
