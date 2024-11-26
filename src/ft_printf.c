#include "ft_printf.h"

int	ft_nbr(int nb)
{
	char			c;
	int				count;
	unsigned int	n;

	count = 0;
	if (nb < 0)
	{
		count += ft_char('-');
		n = (unsigned int)(-nb);
	}
	else
		n = (unsigned int)nb;
	if (n >= 10)
		count += ft_nbr(n / 10);
	c = n % 10 + '0';
	count += ft_char(c);
	return (count);
}

int	ft_print_formats(int i, const char *str, va_list args)
{
	int	count;

	count = 0;
	if (str[i] == 'c')
		count += ft_char(va_arg(args, int));
	else if (str[i] == 's')
		count += ft_str(va_arg(args, char *));
	else if (str[i] == 'p')
		count += ft_ptr(va_arg(args, void *));
	else if (str[i] == 'd' || str[i] == 'i')
		count += ft_nbr(va_arg(args, int));
	else if (str[i] == 'u')
		count += ft_unsigned(va_arg(args, unsigned int));
	else if (str[i] == 'x')
		count += ft_hex(va_arg(args, unsigned int));
	else if (str[i] == 'X')
		count += ft_upper_hex(va_arg(args, unsigned int));
	else if (str[i] == '%')
		count += ft_char('%');
	return (count);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		count;
	int		i;

	va_start(args, str);
	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '%' && str[i + 1])
		{
			i++;
			count += ft_print_formats(i, str, args);
		}
		else
			count += ft_char(str[i]);
		i++;
	}
	va_end(args);
	return (count);
}
