#include "ft_printf.h"
#include "libft.h"

int	ft_str(char *str)
{
	int	count;

	if (str == NULL)
		return (ft_str("(null)"));
	count = 0;
	while (*str)
		count += ft_char(*str++);
	return (count);
}
