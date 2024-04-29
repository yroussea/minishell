/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   better_fnct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basverdi <basverdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 13:23:27 by yroussea          #+#    #+#             */
/*   Updated: 2024/04/29 14:09:38 by basverdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_bool	ft_close(int nb, ...)
{
	va_list	args;
	int		error;
	int		fd;

	error = 0;
	va_start(args, nb);
	while (nb--)
	{
		fd = va_arg(args, int);
		if (fd < 0)
			error += ERROR;
		else
		{
			if (close(fd) == -1)
				error += -1;
		}
	}
	va_end(args);
	if (error != 0)
	{
		ft_printf_fd(2, ERROR_CLOSE);
		return (ERROR);
	}
	return (TRUE);
}

t_bool	ft_dup2(int first_fd, int second_fd)
{
	if (first_fd < 0 || second_fd < 0)
	{
		ft_printf_fd(2, ERROR_DUP);
		return (ERROR);
	}
	if (dup2(first_fd, second_fd) == ERROR)
	{
		ft_printf_fd(2, ERROR_DUP);
		return (ERROR);
	}
	return (TRUE);
}

t_bool	ft_pipe(int fd_pipe[2])
{
	if (pipe(fd_pipe) == ERROR)
	{
		ft_printf_fd(2, ERROR_PIPE);
		return (ERROR);
	}
	return (TRUE);
}

int	ft_fork(void)
{
	int	pid;

	pid = fork();
	if (pid < 0)
		ft_printf_fd(2, ERROR_FORK);
	return (pid);
}

t_lst_envp	*index_removed_var(t_lst_envp *lst_envp, char *key)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(key);
	while (lst_envp && ft_strncmp(lst_envp->key, key, len))
	{
		lst_envp = lst_envp->next;
		i += 1;
	}
	if (ft_strncmp(lst_envp->key, key, len) != 0)
		return (NULL);
	return (lst_envp);
}

void	remove_var_env(t_lst_envp **lst_envp, char *variable)
{
	char		**splited;
	t_lst_envp	*tmp;
	t_lst_envp	*checkpoint;

	if (!*lst_envp)
		return ;
	splited = ft_split_first_sep(variable, '=');
	if (ft_strncmp((*lst_envp)->key, *splited, ft_strlen(*splited)) == 0)
	{
		tmp = *lst_envp;
		*lst_envp = (*lst_envp)->next;
		ft_free_split(splited);
		ft_magic_free("%1 %1 %1", tmp->key, tmp->value, tmp);
		return ;
	}
	checkpoint = index_removed_var(*lst_envp, *splited);
	ft_free_split(splited);
	if (checkpoint == NULL)
		return ;
	tmp = *lst_envp;
	while (tmp->next != checkpoint)
		tmp = tmp->next;
	tmp->next = tmp->next->next;
	ft_magic_free("%1 %1 %1", checkpoint->key, checkpoint->value, checkpoint);
}
