#include "ft_printf.h"

int	ft_char(int c)
{
	return (write (1, &c, 1));
}
