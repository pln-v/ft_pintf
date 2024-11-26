#include "ft_printf.h"
#include "libft.h"

int	ft_upper_hex(unsigned int n)
{
	char	*str;
	int		count;
	int		i;

	count = 0;
	str = ft_itoa_base(n, 16);
	if (str)
	{
		i = 0;
		while (str[i])
		{
			if (str[i] >= 'a' && str[i] <= 'f')
				str[i] -= 32;
			i++;
		}
		count = ft_str(str);
		free(str);
	}
	return (count);
}
