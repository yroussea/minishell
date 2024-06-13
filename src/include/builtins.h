/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basverdi <basverdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 18:00:58 by basverdi          #+#    #+#             */
/*   Updated: 2024/06/13 14:49:45 by basverdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

void	ft_cd(t_node *node);
void	ft_echo(t_node *node);
void	ft_env(t_node *node, char *str, int type);
void	ft_exit(t_node *node, t_bool frompipe);
void	ft_export(t_node *node);
void	ft_pwd(t_node *node);
void	ft_unset(t_node *node, char *arg);

void	close_redir_builtin(t_node *node);

#endif
