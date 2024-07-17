/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basverdi <basverdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 20:54:06 by yroussea          #+#    #+#             */
/*   Updated: 2024/07/17 14:11:40 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "struct.h"

typedef struct s_fds
{
	int	in;
	int	out;
}				t_fds;

typedef enum s_from_pipe
{
	NO_PIPE,
	LEFT_PIPE,
	RIGHT_PIPE,
}			t_from_pipe;

typedef enum s_priority
{
	LEFT,
	RIGHT,
}			t_priority;

typedef enum s_builtin
{
	NOT_A_BUILTIN,
	ECHO,
	EXIT,
	PWD,
	CD,
	EXPORT,
	UNSET,
	ENV,
	CAT,
}			t_builtin;

typedef struct s_lst_ope
{
	t_type_of_node		type;
	struct s_lst_ope	*next;
}				t_lst_ope;

typedef struct s_lst_redir
{
	t_type_of_node		type;
	char				*file;
	int					heredoc_fd;
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

typedef struct s_stack_pipe
{
	int					pipe[2];
	struct s_stack_pipe	*next;
}				t_stack_pipe;

typedef struct s_data_stk
{
	t_stack_pipe	**pipes;
	t_stack_id		**pids;
}				t_data_stk;

typedef struct s_node
{
	t_type_of_node	type;
	char			*cmd;
	char			**args;
	t_lst_redir		*redir;
	struct s_node	*left;
	struct s_node	*right;
	int				infile;
	int				outfile;
	int				errorfile;
	t_lst_envp		**envp;
}			t_node;

void			exec(t_lst_cmd *lst_cmd, t_lst_envp **envp);

t_lst_com		*init_node_com(char **s);
void			ft_lst_com_free(t_lst_com *lst);
t_bool			ft_lst_com_add(t_lst_com **lst, char **s);
void			lst_com_add_back(t_lst_com **lst, t_lst_com *new);
t_lst_com		*lst_com_pop(t_lst_com **lst);

t_lst_ope		*init_node_ope(t_type_of_node type);
void			ft_lst_ope_free(t_lst_ope *lst);
t_bool			ft_lst_ope_add(t_lst_ope **lst, t_type_of_node type);
void			lst_ope_add_back(t_lst_ope **lst, t_lst_ope *new);

t_lst_redir		*init_node_redir(t_type_of_node type, char *file);
void			ft_lst_redir_free(t_lst_redir *lst);
t_bool			ft_lst_redir_add(t_lst_redir **lst, t_type_of_node type,
					char *file);
t_bool			ft_lst_redir_heredoc(t_lst_redir **lst, t_type_of_node type,
					int fd);
void			lst_redir_add_back(t_lst_redir **lst, t_lst_redir *new);

t_bool			split_args(char **s, t_lst_com *lst);

// utils

void			ft_close_pipe(t_stack_pipe **pipe);
void			wait_all(t_stack_id **stk, int checkpoint);
void			close_pipes(t_stack_pipe **stk_pipe);
t_bool			no_replace_heredoc(char *str);
void			replace_fds(int fds_in, int fds_out, int fds_error, t_fds fds);
t_bool			only_space(char **strs);
t_data_stk		*init_stks(void);
t_bool			invalide_single_redir(t_lst_redir *redir);
t_bool			invalide_redir_sep(t_lst_redir *redir, char **error);
int				count_space(char *str, int need_free);
void			exit_cmd(char *full_cmd, t_node *node, char **envp, \
	int exitcode);
t_bool			verif_complete_tree(t_node *root);
void			check_status(int status);

void			fake_pid(int exit_code, t_data_stk *stks);
t_bool			ft_stk_pipe_add(t_stack_pipe **stk, int fds_pipe[2]);
t_stack_pipe	*init_stk_pipe(int fds_pipe[2]);
void			ft_stk_pipe_free(t_stack_pipe *stk);
t_stack_pipe	*stk_pipe_pop(t_stack_pipe **stk);
void			stk_pipe_add_front(t_stack_pipe **stk, t_stack_pipe *new);

void			stk_pid_add_front(t_stack_id **stk, t_stack_id *new);
int				stk_pid_pop(t_stack_id **stk);
void			ft_stk_pid_free(t_stack_id *stk);
t_stack_id		*init_stk_pid(int s);
t_bool			ft_stk_pid_add(t_stack_id **stk, int pid);
/*
 * tree
 */
t_bool			add_child(t_node *root, t_node *new_node, t_priority prio);
t_node			*init_node(t_type_of_node type);
t_bool			ft_add_all_leaf(t_node **node, t_lst_com *cmd, t_lst_envp \
					**envp);
t_bool			ft_add_all_branch(t_node **node, t_lst_ope *ope);
void			ft_free_tree(t_node *root);
t_bool			fill_node(t_node *node, t_lst_com *cmd);

t_bool			exec_tree(t_node *root, t_from_pipe from_pipe, t_data_stk *stks,
					t_fds fds);
t_bool			exec_pipe(t_node *node, t_from_pipe from_pipe, t_data_stk *stks,
					t_fds fds);
t_bool			exec_and(t_node *node, t_from_pipe from_pipe, t_data_stk *stks,
					t_fds fds);
t_bool			exec_or(t_node *node, t_from_pipe from_pipe, t_data_stk *stks,
					t_fds fds);
t_bool			exec_cmd(t_node *node, t_from_pipe from_pipe, t_data_stk *stks,
					t_fds fds);
/*
 * redir
 */
int				ft_heredoc(char *eof);
char			*get_access(t_lst_envp *lst_envp, char *cmd);
t_bool			print_error_access(t_error error_type, char *cmd, char *s);
int				heredoc_reopen(int fd, t_lst_envp *lst_envp);

t_bool			all_redir_builtin(t_node *node, t_lst_redir *redir, \
					t_lst_envp *lst_envp);
t_bool			all_redir_cmd(t_lst_redir *redir, t_fds fds, t_lst_envp \
					*lst_envp);

t_builtin		is_builtin(t_node *node);
t_bool			ft_exec_builtin(t_node *node, t_from_pipe from_pipe, \
					t_data_stk *stks, t_fds fds);
int				redir_heredoc(int fds_in, t_lst_redir *redir, t_lst_envp \
					*lst_envp);
int				redir_infile(int fds_in, t_lst_redir *redir);
int				redir_add(int fds_out, t_lst_redir *redir);
int				redir_out(int fds_out, t_lst_redir *redir);
int				redir_error(int fds_error, t_lst_redir *redir);
void			swap_unquate(char **str, t_lst_envp *envp, \
					char **trimed, char **s);

#endif
