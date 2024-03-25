/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basverdi <basverdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 17:25:08 by yroussea          #+#    #+#             */
/*   Updated: 2024/03/25 16:54:19 by yroussea         ###   ########.fr       */
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

char	**parse_quote(char	**cmd_and_args, t_lst_envp *lst_envp)
{
	int		i;
	char	**result;

	i = ft_str_str_len(cmd_and_args);
	result = ft_calloc(sizeof(char *), i + 1);
	i = 0;
	while (result && cmd_and_args && *(cmd_and_args + i))
	{
		result[i] = ft_unquote(*(cmd_and_args + i), lst_envp);
		if (!result[i])
		{
			ft_free_split(result);
			return (cmd_and_args);
		}
		i += 1;
	}
	if (!result)
		return (cmd_and_args);
	ft_free_split(cmd_and_args);
	return (result);
}

void	test(char **args, t_lst_cmd **lst_cmd, t_lst_envp *lst_envp)
{
	int				i;
	char			**cmd_and_arg;
	char			*tmp;

	i = 0;
	while (args && args[i])
	{
		tmp = ft_vjoin(2, "", " ", args[i]);
		cmd_and_arg = va_tokeniser(tmp, 6, ">>", " 2>", ">", "<<", "<", " ");
		char	**strs = parse_quote(cmd_and_arg, lst_envp); //a enlever :)
		//(void)lst_envp;
		//char	**strs = cmd_and_arg;
		ft_printf_fd(2, "cmd: %S\n", strs);
		if (!ft_lst_cmd_add(lst_cmd, strs, get_type(args[i])))
			*lst_cmd = NULL;
		i += 1;
		free(tmp);
	}
}

t_lst_cmd	*parsing(char *line, t_lst_envp *lst_envp)
{
	char			**args;
	t_lst_cmd		*lst_cmd;

	lst_cmd = NULL;
	args = va_tokeniser(line, 3, "||", "&&", "|"); //parenthese et ;
	test(args, &lst_cmd, lst_envp);
	ft_magic_free("%1 %2", line, args);
	return (lst_cmd);
}
