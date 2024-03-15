/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 20:59:05 by yroussea          #+#    #+#             */
/*   Updated: 2024/03/15 18:14:20 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef parsing_H
# define parsing_H

typedef enum s_quote
{
	NONE,
	SIMPLE,
	DOUBLE,
}			t_quote;

char		**va_tokeniser(char *s, int nb, ...);
t_lst_cmd	*parsing(char *line);

#endif
