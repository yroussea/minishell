/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basverdi <basverdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 13:08:05 by yroussea          #+#    #+#             */
/*   Updated: 2024/07/17 13:11:34 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_isalpha(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

int	ft_isnum(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else if (c == '-' || c == '+' || c == '/')
		return (1);
	return (0);
}

int	ft_iswhitespace(int c)
{
	return (c == ' ' || c == '\n' || c == '\t' \
		|| c == '\v' || c == '\r' || c == '\f');
}
