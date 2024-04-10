/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basverdi <basverdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 14:19:31 by basverdi          #+#    #+#             */
/*   Updated: 2024/04/10 19:47:23 by basverdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

extern int	g_exitcode;

void	ft_pwd(t_node *node)
{
	char	buf[10000];

	getcwd(buf, 10000);
	ft_printf_fd(node->outfile, "%s\n", buf);
	g_exitcode = 0;
}
