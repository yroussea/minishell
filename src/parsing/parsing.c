/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 17:25:08 by yroussea          #+#    #+#             */
/*   Updated: 2024/03/12 19:51:02 by yroussea         ###   ########.fr       */
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

t_lst_cmd	*parsing(char *line)
{
	char			**args;
	int				i;
	t_lst_cmd		*lst_cmd;
	t_type_of_node	type;

	i = 0;
	lst_cmd = NULL;
	args = split_line(line);
	while (args && args[i])
	{
		type = get_type(args[i]);
		if (!ft_lst_cmd_add(&lst_cmd, unzoom(args[i]), type))
		{
			ft_lst_cmd_free(lst_cmd);
			ft_magic_free("%2 %1", args, line);
			return (NULL);
		}
		i += 1;
	}
	ft_magic_free("%2 %1", args, line);
	return (lst_cmd);
}
