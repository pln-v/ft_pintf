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
