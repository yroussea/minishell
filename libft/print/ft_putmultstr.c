/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putmultstr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 07:36:50 by yroussea          #+#    #+#             */
/*   Updated: 2024/01/16 07:36:51 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_putmultstr(char **strs)
{
	size_t	i;
	size_t	k;

	k = 0;
	i = 0;
	while (strs && strs[k])
	{
		i += ft_printf("%s\n", strs[k]);
		k += 1;
	}
	return (i);
}
