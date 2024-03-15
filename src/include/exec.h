/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 20:54:06 by yroussea          #+#    #+#             */
/*   Updated: 2024/03/15 21:49:07 by yroussea         ###   ########.fr       */
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
	struct s_lst_redir	*next;
}				t_lst_redir;

typedef struct s_lst_com
{
	char		*cmd;
	char		**args;
	t_lst_redir	*redir;
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

void		ft_print_lst(int fd, t_lst_cmd *lst);
void		exec(t_lst_cmd *lst_cmd);

#endif
