/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basverdi <basverdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 17:25:08 by yroussea          #+#    #+#             */
/*   Updated: 2024/03/26 16:32:46 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_type_of_node	get_type(char *s)
{
	if (ft_strncmp(s, "||", 3) == 0)
		return (OR);
	if (ft_strncmp(s, "|", 2) == 0)
		return (PIPE);
	if (ft_strncmp(s, "&&", 3) == 0)
		return (AND);
	if (ft_strncmp(s, " 2>", 3) == 0)
		return (DIRE_TWO);
	if (ft_strncmp(s, ">>", 2) == 0)
		return (ADD);
	if (ft_strncmp(s, "<<", 2) == 0)
		return (HEREDOC);
	if (ft_strncmp(s, "<", 1) == 0)
		return (DIRE_IN);
	if (ft_strncmp(s, ">", 1) == 0)
		return (DIRE_OUT);
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


void	test(char **args, t_lst_cmd **lst_cmd)
{
	int				i;
	char			**cmd_and_arg;
	char			*tmp;

	i = 0;
	while (args && args[i])
	{
		tmp = ft_vjoin(2, "", " ", args[i]);
		cmd_and_arg = va_tokeniser(tmp, 6, ">>", " 2>", ">", "<<", "<", " ");
		if (!ft_lst_cmd_add(lst_cmd, cmd_and_arg, get_type(args[i])))
			*lst_cmd = NULL;
		i += 1;
		free(tmp);
	}
}

t_lst_cmd	*parsing(char *line)
{
	char			**args;
	t_lst_cmd		*lst_cmd;

	lst_cmd = NULL;
	args = va_tokeniser(line, 3, "||", "&&", "|"); //parenthese et ;
	test(args, &lst_cmd);
	ft_magic_free("%1 %2", line, args);
	return (lst_cmd);
}
