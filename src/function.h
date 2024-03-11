/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 15:12:07 by yroussea          #+#    #+#             */
/*   Updated: 2024/03/11 19:36:12 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTION_H
# define FUNCTION_H

#include "struct.h"
t_bool		ft_close(int nb, ...);
t_bool		ft_dup2(int first_fd, int second_fd);
t_bool		ft_pipe(int fd_pipe[2]);
int			ft_fork(void);

t_lst_cmd	*parsing(char *line);
void		ft_print_lst(int fd, t_lst_cmd *lst);

#endif
