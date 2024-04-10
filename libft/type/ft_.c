#define LLMAX "9223372036854775807"
#define LLMIN "9223372036854775808"
typedef enum s_bool
{
	ERROR = -1,
	FALSE,
	TRUE,
}				t_bool;
#include <stdio.h>
#include <unistd.h>


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

long long	ft_atoll(char *s)
{
	long long	result;
	int			neg;

	result = 0;
	neg = 1;
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

static t_bool	check_nb_to_big(char *s)
{
	size_t	i;
	int		neg;

	i = 0;
	neg = 0;
	if (!is_nb(s))
		return (TRUE);
	neg = (*s == '-') * -1 + (*s == '+') * 1;
	while (s && *s == '0' || *s == '+' || *s == '-')
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