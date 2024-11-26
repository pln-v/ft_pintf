#include "ft_printf.h"
#include "libft.h"

int	ft_ptr(void *ptr)
{
	unsigned long	n;
	char			*str;
	int				count;

	if (!ptr)
		return (ft_str("(nil)"));
	n = (unsigned long)ptr;
	count = write(1, "0x", 2);
	str = ft_itoa_base(n, 16);
	count += ft_str(str);
	if (!str)
		return (0);
	free(str);
	return (count);
}
