#include "ft_printf.h"
#include "libft.h"

int	ft_hex(unsigned int n)
{
	int		count;
	char	*str;

	count = 0;
	str = ft_itoa_base(n, 16);
	if (str)
	{
		count = ft_str(str);
		free(str);
	}
	return (count);
}
