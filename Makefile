NAME = libftprintf.a

LIBFT_PATH = ./libft
LIBFT = ./libft/libft.a 

CC = cc
CFLAGS = -Wall -Wextra -Werror -I includes -I libft
RM = rm -f

SRCDIR = ./src
INCDIR = ./includes

SRC = $(SRCDIR)/ft_printf.c $(SRCDIR)/ft_unsigned.c $(SRCDIR)/ft_hex.c \
      $(SRCDIR)/ft_upper_hex.c $(SRCDIR)/ft_str.c $(SRCDIR)/ft_char.c \
      $(SRCDIR)/ft_ptr.c

OBJ = $(SRC:.c=.o)

.c.o:
		$(CC) $(CFLAGS) -c $< -o $@
		
all: $(LIBFT) $(NAME)

$(LIBFT):
	make -C $(LIBFT_PATH)

$(NAME): $(OBJ)
	cp $(LIBFT) $(NAME)
	ar rcs $(NAME) $(OBJ)

test: $(LIBFT) test.o $(NAME)
	cc $(CFLAGS) -o test test.o $(LIBFT) $(NAME)
	@echo "Test program compiled."

test.o: test.c
	cc $(CFLAGS) -c test.c -o test.o

clean:
	make clean -C $(LIBFT_PATH)
	$(RM) $(OBJ) test.o

fclean: clean
	$(RM) $(NAME) test
	make fclean -C $(LIBFT_PATH)

re: fclean all

.PHONY:	all clean fclean re libft test
