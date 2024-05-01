/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basverdi <basverdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:53:22 by basverdi          #+#    #+#             */
/*   Updated: 2024/05/01 15:56:23 by basverdi         ###   ########.fr       */
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
		if (!ft_isalnum(var[i]) && var[i] != '=' && var[i] != '\'' && var[i] != '\"')
		{
			ft_printf_fd(node->outfile, \
				"bash: export: `%s': not a valid identifier\n", var);
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
	ft_printf("var[0] = %s\ntmp = %s\n", variable[0], tmp);
	if (tmp)
		ft_unset(node, variable[0]);
	free(tmp);
	ft_free_split(variable);
	lst_envp_add(node->envp, ft_strdup(arg));
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
	if (arg)
	{
		splited = ft_split_first_sep(arg, '=');
		if (!is_forbidden(node, splited[0]))
			create_env(node, arg);
		ft_magic_free("%2", splited);
		return ;
	}
	n = 1;
	while (n < i)
	{
		splited = ft_split_first_sep(node->args[n], '=');
		if (!is_forbidden(node, splited[0]))
			create_env(node, node->args[n]);
		n += 1;
		ft_magic_free("%2", splited);
	}
}
