/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basverdi <basverdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 14:19:31 by basverdi          #+#    #+#             */
/*   Updated: 2024/06/12 19:33:01 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_pwd(t_node *node)
{
	char	buf[4096];

	getcwd(buf, 4096);
	ft_printf_fd(node->outfile, "%s\n", buf);
	get_set_exit_code(0);
}
