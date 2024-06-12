/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basverdi <basverdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 13:28:50 by basverdi          #+#    #+#             */
/*   Updated: 2024/06/12 19:32:39 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
			get_set_exit_code(1);
			ft_printf_fd(node->errorfile, \
				"petite-coquille: cd: OLDPWD not set\n");
			return (FALSE);
		}
	}
	return (FALSE);
}

t_bool	cd_err(t_node *node)
{
	if (ft_str_str_len(node->args) > 2)
	{
		get_set_exit_code(1);
		ft_printf_fd(node->errorfile, \
			"petite-coquille: cd: too many arguments\n");
		return (TRUE);
	}
	if (get_set_exit_code(-1) != 0)
	{
		get_set_exit_code(1);
		ft_printf_fd(node->errorfile, \
			"petite-coquille: cd: %s: No such file or directory\n", \
			node->args[1]);
	}
	return (FALSE);
}

void	ft_cd(t_node *node)
{
	static char	buf[4096];
	char		*var;

	if (cd_err(node))
		return ;
	if (go_to_oldpwd(node))
		return ;
	getcwd(buf, 4096);
	var = ft_vjoin(2, "", "OLDPWD=", buf);
	ft_export(node, var);
	free(var);
	if (ft_str_str_len(node->args) < 1)
		chdir("~/");
	else
		chdir(node->args[1]);
	getcwd(buf, 4096);
	var = ft_vjoin(2, "", "PWD=", buf);
	ft_export(node, var);
	free(var);
	get_set_exit_code(errno);
	cd_err(node);
}
