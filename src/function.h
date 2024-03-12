/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 15:12:07 by yroussea          #+#    #+#             */
/*   Updated: 2024/03/12 20:10:28 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTION_H
# define FUNCTION_H

# include "struct.h"

t_bool		ft_close(int nb, ...);
t_bool		ft_dup2(int first_fd, int second_fd);
t_bool		ft_pipe(int fd_pipe[2]);
int			ft_fork(void);

t_lst_cmd	*parsing(char *line);
void		ft_print_lst(int fd, t_lst_cmd *lst);

t_lst_envp	*init_lst_envp(char **envp);
t_bool		lst_envp_add(t_lst_envp **lst_envp, char *variable);
void		lst_envp_add_order(t_lst_envp **lst_envp, t_lst_envp *new, \
		size_t len);
void		free_lst_envp(t_lst_envp *lst_envp);
t_lst_envp	*init_node_envp(char *key, char *value);
int			envp_lst_len(t_lst_envp *lst_envp);
char		**envp_to_char(t_lst_envp *lst_envp);
char		**get_all_path(t_lst_envp *lst_envp);
char		*get_envp_variable(t_lst_envp *lst_envp, char *variable);
int			get_os(t_lst_envp *lst_envp);

char		*get_prompt(t_lst_envp	*lst_envp);


t_lst_cmd	*init_node_cmd(char **s, t_type_of_node type);
void		ft_lst_cmd_free(t_lst_cmd *lst);
t_bool		ft_lst_cmd_add(t_lst_cmd **lst, char **s, t_type_of_node type);
void		lst_cmd_add_back(t_lst_cmd **lst, t_lst_cmd *new);

#endif
