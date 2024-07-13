/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basverdi <basverdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 13:28:50 by basverdi          #+#    #+#             */
/*   Updated: 2024/07/13 17:20:18 by basverdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <asm-generic/errno.h>

t_bool	go_to_oldpwd(t_node *node)
{
	char	*var;

	if (node->args[1] && ft_strncmp(node->args[1], "-", 1) == 0)
	{
		var = get_envp_variable(*node->envp, "OLDPWD", 1);
		if (var)
		{
			node->args[1] = var;
			ft_cd(node);
			return (TRUE);
		}
		else
		{
			get_set_exit_code(1, TRUE);
			ft_printf_fd(node->errorfile, \
				"petite-coquille: cd: OLDPWD not set\n");
			return (FALSE);
		}
	}
	return (FALSE);
}

t_bool	cd_err(t_node *node, int error_code)
{
	static char	*error_msg[4] = {CDNOFILE, CDPERM, CDNOTDIR, CDNAMELONG};

	if (!node->args[1])
	{
		get_set_exit_code(0, TRUE);
		return (FALSE);
	}
	if (ft_str_str_len(node->args) > 2)
	{
		get_set_exit_code(1, TRUE);
		ft_printf_fd(node->errorfile, CDTOOMANY);
		return (TRUE);
	}
	if (error_code != 0)
	{
		get_set_exit_code(1, TRUE);
		ft_printf_fd(node->errorfile, CDERROR, node->args[1], \
			error_msg[(error_code / 10) % 4]);
	}
	return (FALSE);
}

int	modif_envp(t_lst_envp *lst_envp, char *variable, char *new_value, \
int active)
{
	while (lst_envp)
	{
		if (ft_strncmp(lst_envp->key, variable, ft_strlen(variable) + 1) == 0)
		{
			if (active != -2)
			{
				free(lst_envp->value);
				lst_envp->value = new_value;
				lst_envp->active = active;
			}
			return (lst_envp->active);
		}
		lst_envp = lst_envp->next;
	}
	return (-2);
}

t_bool	get_new_pwd(t_node *node, t_bool pwd)
{
	static char	buf[4096];
	int			active;
	int			active_old;
	char		*var;

	if (pwd)
	{
		if (getcwd(buf, 4096))
		{
			active = modif_envp(*node->envp, "PWD", NULL, -2);
			modif_envp(*node->envp, "PWD", ft_strdup(buf), \
			ft_vmax(2, active, 0));
		}
		else
			return (FALSE);
	}
	else
	{
		var = get_envp_variable(*node->envp, "PWD", -1);
		active = modif_envp(*node->envp, "PWD", NULL, -2);
		active_old = modif_envp(*node->envp, "OLDPWD", NULL, -2);
		check_active(&active, &active_old);
		modif_envp(*node->envp, "OLDPWD", var, active);
	}
	return (TRUE);
}

void	ft_cd(t_node *node)
{
	char	*path;

	path = NULL;
	if (cd_err(node, 0))
		return ;
	if (go_to_oldpwd(node))
		return ;
	if (ft_str_str_len(node->args) == 1)
	{
		path = get_envp_variable(*node->envp, "HOME", 1);
		if (!path)
		{
			ft_printf_fd(node->outfile, "petite-coquille: cd: HOME not set\n");
			get_set_exit_code(1, TRUE);
			return ;
		}
		move_to_dir(path, node);
		free(path);
	}
	else
		move_to_dir(node->args[1], node);
}
