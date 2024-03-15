/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 17:25:08 by yroussea          #+#    #+#             */
/*   Updated: 2024/03/15 12:27:42 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**split_line(char *line)
{
	return (ft_split(line, ' '));
}

t_type_of_node	get_type(char *s)
{
	if (ft_strncmp(s, "||", 3) == 0)
		return (OR);
	if (ft_strncmp(s, "|", 2) == 0)
		return (PIPE);
	if (ft_strncmp(s, "&&", 3) == 0)
		return (AND);
	if (ft_strncmp(s, "2>", 3) == 0)
		return (DIRE_TWO);
	if (ft_strncmp(s, ">>", 3) == 0)
		return (ADD);
	if (ft_strncmp(s, "<<", 3) == 0)
		return (HEREDOC);
	if (ft_strncmp(s, "<", 2) == 0)
		return (DIRE_IN);
	if (ft_strncmp(s, "$", 1) == 0)
		return (VARIABLE);
	if (ft_strncmp(s, "-", 1) == 0)
		return (FLAG);
	return (CMD);
}

char	**unzoom(char *s)
{
	char	**unzoomed;

	unzoomed = ft_calloc(2, sizeof(char *));
	if (unzoomed)
	{
		unzoomed[0] = ft_strdup(s);
		unzoomed[1] = NULL;
	}
	return (unzoomed);
}

int	get_successive_cmd(char ***cmd_and_arg, char **args)
{
	int		i;
	char	**tmp;

	i = 0;
	tmp = NULL;
	while (args && args[i] && get_type(args[i]) == CMD)
	{
		tmp = ft_str_realloc(tmp);
		if (tmp)
			tmp[ft_str_str_len(tmp)] = ft_strdup(args[i]);
		else
		{
			i += 1;
			break ;
		}
		i += 1;
	}
	*cmd_and_arg = tmp;
	return (i);
}

void	test(char **args, t_lst_cmd **lst_cmd)
{
	int				i;
	t_type_of_node	type;
	char			**cmd_and_arg;

	i = 0;
	while (args && args[i])
	{
		type = get_type(args[i]);
		cmd_and_arg = NULL;
		if (type == CMD)
			i += get_successive_cmd(&cmd_and_arg, args + i);
		else
			cmd_and_arg = unzoom(args[i++]);
		if (!ft_lst_cmd_add(lst_cmd, cmd_and_arg, type))
			*lst_cmd = NULL;
	}
}

t_lst_cmd	*parsing(char *line)
{
	char			**args;
	t_lst_cmd		*lst_cmd;

	lst_cmd = NULL;
//	args = split_line(line);
//	test(args, &lst_cmd);
	args = va_tokeniser(line, 6, "||", "&&", "|", ";", "(", ")");
	ft_printf("%S", args);
	ft_magic_free("%1 %2", line, args);
	return (lst_cmd);
}
