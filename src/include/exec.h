/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 20:54:06 by yroussea          #+#    #+#             */
/*   Updated: 2024/03/16 15:07:10 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

typedef enum s_priority
{
	LEFT,
	RIGHT,
}		t_priority;

typedef struct s_lst_ope
{
	t_type_of_node		type;
	struct s_lst_ope	*next;
}				t_lst_ope;

typedef	struct s_lst_redir
{
	t_type_of_node		type;
	char				*file;
	struct s_lst_redir	*next;
}				t_lst_redir;

typedef struct s_lst_com
{
	char				*cmd;
	char				**args;
	t_lst_redir			*redir;
	struct s_lst_com	*next;
}				t_lst_com;

typedef struct s_stack_id
{
	int					pid;
	struct s_stack_id	*next;
}				t_stack_id;

typedef struct s_node
{
	t_type_of_node	type;
	char			*cmd;
	char			**args;
	int				infile;
	int				outfile;
	struct s_node	*left;
	struct s_node	*right;
}				t_node;

void		ft_print_ope(int fd, t_lst_ope *lst);
void		ft_print_redir(int fd, t_lst_redir *lst);
void		ft_print_com(int fd, t_lst_com *lst);
void		ft_print_lst(int fd, t_lst_cmd *lst);
void		ft_print_tree(t_node *root);
void		ft_print_node(t_node *node);

void		exec(t_lst_cmd *lst_cmd);

t_lst_com	*init_node_com(char **s);
void		ft_lst_com_free(t_lst_com *lst);
t_bool		ft_lst_com_add(t_lst_com **lst, char **s);
void		lst_com_add_back(t_lst_com **lst, t_lst_com *new);

t_lst_ope	*init_node_ope(t_type_of_node type);
void		ft_lst_ope_free(t_lst_ope *lst);
t_bool		ft_lst_ope_add(t_lst_ope **lst, t_type_of_node type);
void		lst_ope_add_back(t_lst_ope **lst, t_lst_ope *new);

t_lst_redir	*init_node_redir(t_type_of_node type, char *file);
void		ft_lst_redir_free(t_lst_redir *lst);
t_bool		ft_lst_redir_add(t_lst_redir **lst, t_type_of_node type, char *file);
void		lst_redir_add_back(t_lst_redir **lst, t_lst_redir *new);

t_bool		split_args(char **s, t_lst_com *lst);

#endif
