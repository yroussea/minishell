/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parting.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 20:59:05 by yroussea          #+#    #+#             */
/*   Updated: 2024/03/15 10:39:04 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARTING_H
# define PARTING_H

char		**va_tokeniser(char *s, int nb, ...);
t_lst_cmd	*parsing(char *line);

#endif
