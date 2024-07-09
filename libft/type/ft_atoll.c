/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basverdi <basverdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 15:52:23 by bastienverd       #+#    #+#             */
/*   Updated: 2024/07/09 09:14:38 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

long long	ft_atoll(char *s)
{
	long long	result;
	int			neg;

	result = 0;
	neg = 1;
	while (s && *s && *s == ' ')
		s += 1;
	if (*s == '-' || *s == '+')
	{
		neg = (*s == '-') * -1 + (*s == '+') * 1;
		s += 1;
	}
	while (s && *s)
	{
		result = result * 10 + (*s - '0');
		s += 1;
	}
	return (result * neg);
}
