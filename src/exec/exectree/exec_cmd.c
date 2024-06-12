/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basverdi <basverdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 16:56:14 by yroussea          #+#    #+#             */
/*   Updated: 2024/06/12 19:17:45 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**quote_realloc(char **res, char *unqoted)
{
	char	**tmp;
	char	**tab;
	int		i;
	int		j;

	i = -1;
	j = 0;
	tmp = ft_split_out_quote(unqoted, ' ', '\001');
	if (!tmp)
		return (res);
	tab = ft_calloc(sizeof(char *), \
	ft_str_str_len(tmp) + ft_str_str_len(res) + 1);
	if (!tab)
	{
		ft_free_split(tmp);
		return (res);
	}
	while (res && *(res + ++i))
		*(tab + i) = ft_strdup(*(res + i));
	while (tmp && *(tmp + j))
		*(tab + i++) = ft_strdupexept(*(tmp + j++), '\001');
	ft_free_split(res);
	ft_free_split(tmp);
	return (tab);
}

void	parse_quote(t_node *node, int j, int i)
{
	char	**res;
	char	*unqoted;

	res = ft_calloc(sizeof(char *), 1);
	while (res && node->args && *(node->args + j))
	{
		unqoted = ft_unquote(*(node->args + j), *(node->envp), 0);
		res = quote_realloc(res, unqoted);
		free(unqoted);
		while (res[i])
			i += 1;
		j += 1;
	}
	if (!res)
		node->cmd = ft_strdup(*node->args);
	if (!res)
		return ;
	node->args = res;
	node->cmd = ft_strdup(*res);
}

void	child_exec_cmd(char *full_cmd, t_node *node, t_fds fds, t_data_stk \
	*stks)
{
	char	**envp_char;

	envp_char = envp_to_char(*node->envp);
	if (envp_char)
	{
		if (all_redir_cmd(node->redir, fds, *node->envp))
		{
			ft_close_pipe(stks->pipes);
			close_heredoc(ft_get_root(NULL, FALSE, FALSE));
			execve(full_cmd, node->args, envp_char);
		}
		else
			ft_close_pipe(stks->pipes);
		get_set_exit_code(1);
	}
	exit_cmd(full_cmd, node, envp_char, get_set_exit_code(-1));
}

void	fake_pid(int exit_code, t_data_stk *stks)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		ft_close_pipe(stks->pipes);
		ft_get_envp(NULL, FALSE, TRUE);
		ft_get_root(NULL, FALSE, TRUE);
		ft_get_lsts(NULL, NULL, FALSE, TRUE);
		ft_get_stks(NULL, FALSE, TRUE);
		rl_clear_history();
		exit(exit_code);
	}
	if (pid > 0)
		ft_stk_pid_add(stks->pids, pid);
}

t_bool	exec_cmd(t_node *node, t_from_pipe from_pipe, t_data_stk *stks, t_fds \
	fds)
{
	int			pid;
	char		*full_cmd;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handler_exec);
	signal(SIGQUIT, handler_exec);
	parse_quote(node, 0, 0);
	if (node->cmd && is_builtin(node))
		return (ft_exec_builtin(node, from_pipe, stks, fds));
	full_cmd = get_access(*(node->envp), node->cmd);
	free(node->cmd);
	if (full_cmd)
	{
		pid = ft_fork();
		if (pid == 0)
			child_exec_cmd(full_cmd, node, fds, stks);
		if (pid > 0)
			ft_stk_pid_add(stks->pids, pid);
		ft_magic_free("%2 %1", node->args, full_cmd);
		return (TRUE);
	}
	all_redir_builtin(node, node->redir, *node->envp);
	close_redir_builtin(node);
	ft_free_split(node->args);
	fake_pid(get_set_exit_code(-1), stks);
	return (ERROR);
}
