/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basverdi <basverdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 18:01:15 by basverdi          #+#    #+#             */
/*   Updated: 2024/06/12 18:01:34 by basverdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	count_space(char *str, int need_free)
{
	int		count;
	char	*tmp;

	count = 0;
	tmp = str;
	while (*str)
	{
		if (*str == ' ')
			count++;
		str++;
	}
	if (need_free)
		free(tmp);
	return (count);
}
