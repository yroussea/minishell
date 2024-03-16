/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_com_split_args.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 12:32:29 by yroussea          #+#    #+#             */
/*   Updated: 2024/03/16 12:41:35 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_bool	split_args(char **s, t_lst_com *lst)
{
	lst->cmd = NULL;
	lst->args = NULL;
	lst->redir = NULL;
	(void)s;
	return (TRUE);
}
