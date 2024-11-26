#ifndef FT_PRINTF_H
# define FT_PRINTF_H 

# include <stdarg.h>
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>

int	ft_printf(const char *str, ...);
int	ft_char(int c);
int	ft_str(char *str);
int	ft_nbr(int nb);
int	ft_ptr(void *ptr);
int	ft_unsigned(unsigned int n);
int	ft_hex(unsigned int n);
int	ft_upper_hex(unsigned int n);
#endif
