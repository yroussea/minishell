/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_overflow.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basverdi <basverdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 17:30:10 by basverdi          #+#    #+#             */
/*   Updated: 2024/07/09 09:14:38 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static t_bool	ft_is_nb(char c)
{
	if (c >= '0' && c <= '9')
		return (TRUE);
	return (FALSE);
}

static t_bool	is_nb(char *s)
{
	if (*s == '-' || *s == '+')
		s++;
	while (s && *s)
	{
		if (ft_is_nb(*s))
			s += 1;
		else
			return (FALSE);
	}
	return (TRUE);
}

static t_bool	check_nb_same_len(char *s, char *max, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		if (*(s + i) > max[i])
			return (TRUE);
		i += 1;
	}
	return (FALSE);
}

t_bool	ft_overflow(char *s)
{
	size_t	i;
	int		neg;

	i = 0;
	neg = 0;
	while (s && *s && *s == ' ')
		s++;
	if (!is_nb(s))
		return (TRUE);
	neg = (*s == '-') * -1 + (*s == '+') * 1;
	while (s && (*s == '0' || *s == '+' || *s == '-'))
		s++;
	while (s && *(s + i))
		i += 1;
	if (i > 19)
		return (TRUE);
	if (i == 19 && neg != -1)
		return (check_nb_same_len(s, LLMAX, 19));
	else if (i == 19)
		return (check_nb_same_len(s, LLMIN, 19));
	return (FALSE);
}
