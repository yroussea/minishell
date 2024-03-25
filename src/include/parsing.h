/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basverdi <basverdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 20:59:05 by yroussea          #+#    #+#             */
/*   Updated: 2024/03/25 14:10:31 by yroussea         ###   ########.fr       */
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

t_type_of_node	get_type(char *s);
char			**va_tokeniser(char *s, int nb, ...);
t_lst_cmd		*parsing(char *line, t_lst_envp *lst_envp);
size_t			len_quote(char *s, t_quote quote);

char			*ft_unquote(char *s, t_lst_envp *lst_envp);

#endif
