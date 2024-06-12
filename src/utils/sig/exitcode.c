/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exitcode.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 18:14:08 by yroussea          #+#    #+#             */
/*   Updated: 2024/06/12 19:14:35 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../..//minishell.h"

int	get_set_exit_code(int code)
{
	static int		exitcode;

	if (code != -1)
		exitcode = code;
	return (exitcode);
}

