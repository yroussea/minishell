/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 09:40:56 by yroussea          #+#    #+#             */
/*   Updated: 2024/07/09 09:14:38 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_atoi(const char *nptr)
{
	int	sign;
	int	i;
	int	result;

	i = 0;
	while (nptr && ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == ' '))
	{
		i += 1;
	}
	if (nptr && (nptr[i] == '+' || nptr[i] == '-'))
	{
		sign = 1 - (2 * (nptr[i] == '-'));
		i += 1;
	}
	else
		sign = 1;
	result = 0;
	while (nptr && (nptr[i] <= '9' && nptr[i] >= '0'))
	{
		result = result * 10 + (nptr[i] - '0');
		i += 1;
	}
	return (sign * result);
}
