/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   magic_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:13:41 by yroussea          #+#    #+#             */
/*   Updated: 2024/07/09 09:14:38 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include "stdint.h"

int	ft_nbr_len(unsigned int nbr)
{
	if (nbr == 0)
		return (0);
	return (1 + ft_nbr_len(nbr / 10));
}

void	ft_recur_free(int depth, void *alloc)
{
	void	*save;

	save = alloc;
	if (depth == 1)
	{
		free(alloc);
		return ;
	}
	if (depth == 2)
	{
		ft_free_split(alloc);
		return ;
	}
	while (alloc && *(char *)alloc)
	{
		ft_recur_free(depth -1, (void *)*(uintptr_t *)alloc);
		alloc += 8;
	}
	free(save);
}

void	ft_magic_free(char *str, ...)
{
	va_list	alloc;
	int		recur;

	if (!str)
		return ;
	va_start(alloc, str);
	while (*str)
	{
		if (*str == '%' && *(str + 1))
		{
			recur = ft_atoi(str + 1);
			ft_recur_free(recur, va_arg(alloc, void *));
			str += ft_nbr_len(recur);
		}
		else
		{
			if (*str == 't')
				free(va_arg(alloc, int *));
			if (*str == 'l')
				ft_lstclear(va_arg(alloc, t_list **), free);
			str += 1;
		}
	}
	va_end(alloc);
}
