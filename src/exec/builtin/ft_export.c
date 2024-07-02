/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basverdi <basverdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:53:22 by basverdi          #+#    #+#             */
/*   Updated: 2024/07/02 15:45:24 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_bool	is_forbidden(t_node *node, char *var)
{
	int	i;

	i = 0;
	if (var && *var)
		return (FALSE);
	while (var[i])
	{
		if ((!ft_isalnum(var[i]) || !ft_isalpha(var[0])) && var[i] != '=' \
			&& var[i] != '\'' && var[i] != '\"' && var[i] != '_' \
			&& (var[i] != '+' && var[i + 1] != '='))
		{
			ft_printf_fd(node->errorfile, \
				"petite-coquille: export: `%s': not a valid identifier\n", \
				var);
			get_set_exit_code(1, TRUE);
			return (TRUE);
		}
		i++;
	}
	return (FALSE);
}

void	concatenate_envp(t_node *node, char **variable, char *tmp2, char *arg)
{
	variable[1] = ft_strdup(tmp2);
	arg = ft_vjoin(3, "", variable[0], "=", variable[1]);
	lst_envp_add(node->envp, ft_strdup(arg));
	ft_magic_free("%1 %1 %2", arg, tmp2, variable);
}

void	create_env(t_node *node, char *arg)
{
	char	**variable;
	char	*tmp;
	char	*tmp2;
	char	*env_var;

	variable = ft_split_first_sep(arg, '=');
	if (variable[0][ft_strlen(variable[0]) - 1] == '+')
	{
		variable[0][ft_strlen(variable[0]) - 1] = '\0';
		env_var = get_envp_variable(*node->envp, variable[0], 1);
		tmp2 = join_and_free(2, "", env_var, variable[1]);
	}
	else
		tmp2 = NULL;
	tmp = is_envp_variable(*node->envp, variable[0]);
	if (tmp)
		ft_unset(node, variable[0]);
	if (tmp2)
		concatenate_envp(node, variable, tmp2, arg);
	else
	{
		lst_envp_add(node->envp, ft_strdup(arg));
		ft_free_split(variable);
	}
	ft_magic_free("%1", tmp);
}

t_bool	check_splited(char **splited, t_node *node)
{
	if (!*splited)
	{
		ft_magic_free("%2", splited);
		ft_printf_fd(node->errorfile, \
		"petite-coquille: export: `=': not a valid identifier\n");
		get_set_exit_code(1, TRUE);
		return (TRUE);
	}
	return (FALSE);
}

void	ft_export(t_node *node)
{
	int		i;
	int		n;
	char	**splited;

	i = ft_str_str_len(node->args);
	if (i == 1)
	{
		display_env(node);
		return ;
	}
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
