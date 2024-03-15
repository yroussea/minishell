/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parting.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basverdi <basverdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 20:59:05 by yroussea          #+#    #+#             */
/*   Updated: 2024/03/15 18:08:20 by basverdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef parsing_H
# define parsing_H

char		**va_tokeniser(char *s, int nb, ...);
t_lst_cmd	*parsing(char *line);

#endif
