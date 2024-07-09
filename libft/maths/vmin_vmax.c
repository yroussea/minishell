/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vmin_vmax.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 10:10:00 by yroussea          #+#    #+#             */
/*   Updated: 2024/07/09 09:14:38 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_vmin(int number_of_number, ...)
{
	va_list	all_numbers;
	int		minimum;
	int		tmp;

	minimum = INT_MAX;
	va_start(all_numbers, number_of_number);
	while (number_of_number)
	{
		tmp = va_arg(all_numbers, int);
		if (tmp < minimum)
			minimum = tmp;
		number_of_number--;
	}
	va_end(all_numbers);
	return (minimum);
}

int	ft_vmax(int number_of_number, ...)
{
	va_list	all_numbers;
	int		maximum;
	int		tmp;

	maximum = INT_MIN;
	va_start(all_numbers, number_of_number);
	while (number_of_number)
	{
		tmp = va_arg(all_numbers, int);
		if (tmp > maximum)
			maximum = tmp;
		number_of_number--;
	}
	va_end(all_numbers);
	return (maximum);
}
