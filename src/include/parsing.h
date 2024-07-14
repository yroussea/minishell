/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basverdi <basverdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 20:59:05 by yroussea          #+#    #+#             */
/*   Updated: 2024/07/14 19:57:55 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

typedef enum s_quote
{
	NONE,
	SIMPLE,
	DOUBLE,
}			t_quote;

void			ft_clear_term(int ac, char **av);
t_type_of_node	get_type(char *s);
char			**va_tokeniser(char *s, int nb, ...);
t_lst_cmd		*parsing(char *line);
size_t			len_quote(char *s, t_quote quote);

char			*strdup_until_sep(char *s, int nb_sep, ...);
char			*ft_unsimplequote(char *s, t_lst_envp *lst_envp, \
					int inside_dollars);
char			*ft_undolars(char *s, t_lst_envp *lst_envp, int inside_dollars);
char			*ft_undoublequote(char *s, t_lst_envp *lst_envp, \
					int inside_dollars);
char			*ft_unquote(char *s, t_lst_envp *lst_envp, int inside_dollars, \
					char *res);
char			*invisible_char(t_bool creat, char *s);

int				is_alphanum_underscore(char c);
char			*strdup_until_funct(char *s, int (f(char c)));

#endif
