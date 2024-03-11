/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 15:12:07 by yroussea          #+#    #+#             */
/*   Updated: 2024/03/11 17:32:39 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTION_H
# define FUNCTION_H

t_bool	ft_close(int nb, ...);
t_bool	ft_dup2(int first_fd, int second_fd);
t_bool	ft_pipe(int fd_pipe[2]);
int		ft_fork(void);

t_lst	*parsing(char *line);
void	ft_print_lst(int fd, t_lst *lst);

#endif
