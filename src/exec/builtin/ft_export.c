/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basverdi <basverdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:53:22 by basverdi          #+#    #+#             */
/*   Updated: 2024/06/09 06:54:29 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

extern int	g_exitcode;

t_bool	is_forbidden(t_node *node, char *var)
{
	int	i;

	i = 0;
	while (var[i])
	{
		if ((!ft_isalnum(var[i]) || !ft_isalpha(var[0])) && var[i] != '=' \
			&& var[i] != '\'' && var[i] != '\"')
		{
			ft_printf_fd(node->errorfile, \
				"petite-coquille: export: `%s': not a valid identifier\n", \
				var);
			g_exitcode = 1;
			return (TRUE);
		}
		i++;
	}
	return (FALSE);
}

void	create_env(t_node *node, char *arg)
{
	char	**variable;
	char	*tmp;

	variable = ft_split_first_sep(arg, '=');
	tmp = is_envp_variable(*node->envp, variable[0]);
	if (tmp)
		ft_unset(node, variable[0]);
	free(tmp);
	ft_free_split(variable);
	lst_envp_add(node->envp, ft_strdup(arg));
}

t_bool	check_splited(char **splited, t_node *node)
{
	if (!*splited)
	{
		ft_magic_free("%2", splited);
		ft_printf_fd(node->errorfile, "petite-coquille: export: `=': not a valid identifier\n");
		g_exitcode = 1;
		return (TRUE);
	}
	return (FALSE);
}

t_bool exec_builtin_env(t_node *node, char *arg)
{
	char	**splited;

	splited = ft_split_first_sep(arg, '=');
	if (check_splited(splited, node))
		return (TRUE);
	if (!is_forbidden(node, splited[0]))
		create_env(node, arg);
	ft_magic_free("%2", splited);
	return (TRUE);
}

void	ft_export(t_node *node, char *arg)
{
	int		i;
	int		n;
	char	**splited;

	i = ft_str_str_len(node->args);
	if (i == 1)
		display_env(node);
	if (i == 1)
		return ;
	if (arg && exec_builtin_env(node, arg))
		return ;
	n = 0;
	while (++n < i)
	{
		splited = ft_split_first_sep(node->args[n], '=');
		if (check_splited(splited, node))
			continue ;
		if (!is_forbidden(node, splited[0]))
			create_env(node, node->args[n]);
		ft_magic_free("%2", splited);
	}
}
