/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basverdi <basverdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 18:00:58 by basverdi          #+#    #+#             */
/*   Updated: 2024/04/10 18:12:33 by basverdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

void	ft_cd(t_node *node);
void	ft_echo(t_node *node);
void	ft_env(t_node *node);
void	ft_exit(t_node *node);
void	ft_pwd(t_node *node);

#endif