/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: basverdi <basverdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 13:15:27 by yroussea          #+#    #+#             */
/*   Updated: 2024/07/09 09:14:38 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_isalnum(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

int	is_alphanum_underscore(char c)
{
	if (ft_isalnum(c))
		return (1);
	return (c == '_');
}
