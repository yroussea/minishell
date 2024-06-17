/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basverdi <basverdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 16:54:24 by basverdi          #+#    #+#             */
/*   Updated: 2024/06/17 18:43:49 by basverdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIG_H
# define SIG_H

void	set_sigaction(int state);
void	handler(int signal);
void	handler_void(int signal);
void	heredoc_handler(int signal);
t_bool	sig_heredoc(char *line, char *eof, int count);
void	free_heredoc(t_bool reset, char *eof, int fd);

#endif