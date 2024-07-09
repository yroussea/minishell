/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 07:34:13 by yroussea          #+#    #+#             */
/*   Updated: 2024/07/09 09:14:38 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static size_t	ft_format(const char *c, va_list args)
{
	if (ft_strnstr(c, "stk", 3))
		return (ft_put_stack(va_arg(args, t_stack *)));
	if (*c == 'S')
		return (ft_putmultstr(va_arg(args, char **)));
	if (*c == 'c')
		return (ft_putlchar(va_arg(args, int)));
	if (*c == 's')
		return (ft_putlstr(va_arg(args, char *)));
	if (*c == 'u')
		return (ft_putlunbr(va_arg(args, unsigned int)));
	if (*c == 'd' || *c == 'i')
		return (ft_putlnbr(va_arg(args, int)));
	if (*c == '%')
		return (ft_putlchar('%'));
	if (*c == 'x')
		return (ft_putlhexa_low(va_arg(args, unsigned int)));
	if (*c == 'X')
		return (ft_putlhexa_up(va_arg(args, unsigned int)));
	if (*c == 'p')
		return (ft_putlpoint(va_arg(args, void *)));
	if (*c == '\0')
		return (-1);
	return (ft_putlchar('%') + ft_putlchar(*c));
}

static int	ft_put_percent(const char *c, va_list args, int *boole, size_t *i)
{
	int	len;

	len = ft_format(c, args);
	if (ft_strnstr(c, "stk", 3))
		*i += 3;
	else if (len == -1)
		*boole = 1;
	else
		*i += 1;
	return (len);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	size_t	i;
	int		len;
	int		boole;

	i = 0;
	len = 0;
	boole = 0;
	if (!str)
		return (-1);
	va_start(args, str);
	while (str[i])
	{
		if (str[i] == '%')
			len += ft_put_percent(str + i + 1, args, &boole, &i);
		else
			len += ft_putlchar(str[i]);
		i += 1;
	}
	va_end(args);
	if (boole)
		return (-1);
	return (len);
}
