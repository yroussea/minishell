#include "../libft.h"

static size_t	ft_format_fd(const char c, va_list args, int fd)
{
	if (c == 'S')
		return (ft_putmultstr_fd(va_arg(args, char **), fd));
	if (c == 'c')
		return (ft_putlchar_fd(va_arg(args, int), fd));
	if (c == 's')
		return (ft_putlstr_fd(va_arg(args, char *), fd));
	if (c == 'u')
		return (ft_putlunbr_fd(va_arg(args, unsigned int), fd));
	if (c == 'd' || c == 'i')
		return (ft_putlnbr_fd(va_arg(args, int), fd));
	if (c == '%')
		return (ft_putlchar_fd('%', fd));
	if (c == 'x')
		return (ft_putlhexa_low_fd(va_arg(args, unsigned int), fd));
	if (c == 'X')
		return (ft_putlhexa_up_fd(va_arg(args, unsigned int), fd));
	if (c == 'p')
		return (ft_putlpoint_fd(va_arg(args, void *), fd));
	if (!c)
		return (-1);
	return (ft_putlchar_fd('%', fd) + ft_putlchar_fd(c, fd));
}

int	ft_printf_fd(int fd, const char *str, ...)
{
	va_list	args;
	int		len;

	len = 0;
	if (!str)
		return (-1);
	va_start(args, str);
	while (str && *str)
	{
		if (*str == '%')
			len += ft_format_fd(*(str + 1), args, fd);
		else
			len += ft_putlchar_fd(*str, fd);
		str += 1;
	}
	va_end(args);
	return (len);
}
