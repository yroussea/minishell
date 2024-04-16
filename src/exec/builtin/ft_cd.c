/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basverdi <basverdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 13:28:50 by basverdi          #+#    #+#             */
/*   Updated: 2024/04/16 18:11:14 by basverdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

extern int	g_exitcode;

void	ft_cd(t_node *node)
{
	char	buf[10000];

	getcwd(buf, 10000);
	ft_export(node, "OLDPWD");
	chdir(node->args[1]);
	getcwd(buf, 10000);
	ft_export(node, "PWD");
	g_exitcode = errno;
}
