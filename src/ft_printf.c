#include "ft_printf.h"

int	ft_char(int c)
{
	return (write (1, &c, 1));
}

int	ft_str(char *str)
{
	int	count;

	count = 0;
	while(*str)
		count += ft_char(*str++);
	return(count);
}

int	ft_nbr(int nb)
{
	char	c;
	int	count;
	unsigned int	n;

	count = 0;	
	if (nb < 0)
	{
		write(1, "-", 1);
		n = (unsigned int)(-nb);
	}
	else		
		n = (unsigned int)nb;
	if (n >= 10)
		ft_nbr(n / 10);
	c = n % 10 + '0';
	count += write(1, &c, 1);
	return (count);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int	count;
	int	i;

	va_start(args, str);
	i = 0;
	while (str[i])
	{
		if (str[i] == '%' && str[i + 1])
		{
			i++;
			if (str[i] == 'c')
				count += ft_char(va_arg(args, int));
			else if (str[i] == 's')
				count += ft_str(va_arg(args, char *));
//			else if (str[i] == 'p')
//				count += ft_ptr(va_arg(args, void *));
			else if (str[i] == 'd' || str[i] == 'i')
				count += ft_nbr(va_arg(args, int));
//			else if (str[i] == 'u')
//				count += ft_unsigned(va_arg(args, ));
//			else if (str[i] == 'x')
//				count += ft_base16(va_arg(args, ));
//			else if (str[i] == 'X')
//				count += ft_base16_upper(va_arg(args, ));
			else if (str[i] == '%')
				count += ft_char('%');
			else
				count += ft_char(str[i]);
		}
		i++;
	}
	return (count);
}

int main()
{
	int	n = 123;
	char	c = 'c';
	char	*s = "you";
	ft_printf("Hello, world\n");
	ft_printf("Hello, %c\n", c);
	ft_printf("Hello, %s\n", s);
	ft_printf("Hello, %i\n", n);
	ft_printf("Hello, %d\n", n);
}
