/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basverdi <basverdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 14:19:31 by basverdi          #+#    #+#             */
/*   Updated: 2024/06/17 18:16:08 by basverdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_pwd(t_node *node)
{
	static char	buf[4096];

	if (getcwd(buf, 4096))
		ft_printf_fd(node->outfile, "%s\n", buf);
	else
		ft_printf_fd(node->outfile, "pwd: %s\n", strerror(errno));
	get_set_exit_code(0, TRUE);
}
