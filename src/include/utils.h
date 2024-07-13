/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basverdi <basverdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 20:52:00 by yroussea          #+#    #+#             */
/*   Updated: 2024/07/13 17:54:16 by basverdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

/*
 * just better fonction
 */
t_bool			ft_close(int nb, ...);
t_bool			ft_dup2(int first_fd, int second_fd);
t_bool			ft_pipe(int fd_pipe[2]);
int				ft_fork(void);
char			ft_random(void);
char			**ft_duptab(char **s, int i, int j);

/*
 * lst_cmd
 */
t_lst_cmd		*init_node_cmd(char **s, t_type_of_node type);
void			ft_lst_cmd_free(t_lst_cmd *lst);
t_bool			ft_lst_cmd_add(t_lst_cmd **lst, char **s, t_type_of_node type);
void			lst_cmd_add_back(t_lst_cmd **lst, t_lst_cmd *new);
t_bool			init_skip(int *j, t_bool skip);
t_bool			is_redir(char *s);

/*
 * lst_envp
 */
t_lst_envp		*init_lst_envp(char **envp);
t_bool			lst_envp_add(t_lst_envp **lst_envp, char *variable);
void			lst_envp_add_order(t_lst_envp **lst_envp, t_lst_envp *new,
					size_t len);
void			free_lst_envp(t_lst_envp *lst_envp);
t_lst_envp		*init_node_envp(char *key, char *value);
int				envp_lst_len(t_lst_envp *lst_envp);
char			**envp_to_char(t_lst_envp *lst_envp);
char			**get_all_path(t_lst_envp *lst_envp);
char			*get_envp_variable(t_lst_envp *lst_envp, char *variable, \
					int exist);
int				get_os(t_lst_envp *lst_envp);
void			remove_var_env(t_lst_envp **lst_envp, char *variable);

/*
 * just a better prompt
 */
char			*get_prompt(t_lst_envp	*lst_envp, char *prompt, int no_color);
t_bool			is_git_file(char *pwd, char **branch);
t_lst_envp		*index_removed_var(t_lst_envp *lst_envp, char *key);
int				modif_envp(t_lst_envp *lst_envp, char *variable, \
				char *new_value, int active);

/*
 * utils parsing
 */
size_t			ft_count_word(char *s, char **token, size_t count);
size_t			len_next_word(char *s, char **token, size_t len);
size_t			len_next_token(char *s, char **token, size_t len);
int				is_token(char *s, char **token);
size_t			jump_quote(char *s, size_t len, size_t *count);
size_t			jump_token(char *s, char **token, size_t *count, t_bool *bool);
int				skip_underscore(char *s);

/*
 * get malloc from anywhere
 */
t_bool			ft_get_lsts(t_lst_ope *ope, t_lst_com *com, t_bool reset, \
					t_bool free_lst);
t_node			*ft_get_root(t_node *node, t_bool reset, t_bool free_tree);
t_data_stk		*ft_get_stks(t_data_stk *stks, t_bool reset, t_bool free_stks);
t_bool			ft_get_envp(t_lst_envp *lst_envp, t_bool reset, t_bool \
					free_envp);
void			close_heredoc(t_node *node);
int				get_set_exit_code(int code, t_bool set);

/*
 * utils builtins
 */
void			display_env(t_node *node);
char			*is_envp_variable(t_lst_envp *lst_envp, char *variable);
char			*join_and_free(size_t nb_str, char *sep, ...);
void			move_to_dir(char *path, t_node *node);
t_bool			get_new_pwd(t_node *node, t_bool pwd);
t_bool			cd_err(t_node *node, int error_code);

t_bool			find_char_in_split(char *s, char **spl);
char			**exec_child_cmd(char **cmd, t_lst_envp *envp);
char			**gnl_all_file(char *file, int *fd);
int				in_child_cmd(char **cmd, t_lst_envp *envp, int fd[2]);
t_bool			diff_lang(char *lang, char *cmp);

#endif
