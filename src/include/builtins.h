/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basverdi <basverdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 18:00:58 by basverdi          #+#    #+#             */
/*   Updated: 2024/04/12 19:39:03 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

void	ft_cd(t_node *node);
void	ft_echo(t_node *node);
void	ft_env(t_node *node);
void	ft_exit(t_node *node, t_bool frompipe);
void	ft_pwd(t_node *node);

void	close_redir_builtin(t_node *node);

#endif
