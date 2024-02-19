/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putlstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 08:14:11 by yroussea          #+#    #+#             */
/*   Updated: 2023/11/05 13:41:50 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_putlstr(char *s)
{
	size_t	i;

	if (s == NULL)
	{
		(write(1, "(null)", 6));
		return (6);
	}
	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i += ft_putlchar(s[i]);
	return (i);
}
