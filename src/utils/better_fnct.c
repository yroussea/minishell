/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   better_fnct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 13:23:27 by yroussea          #+#    #+#             */
/*   Updated: 2024/03/12 15:15:28 by yroussea         ###   ########.fr       */
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
			error += close(fd);
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
