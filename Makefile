NAME = pipex
CFLAGS = -g -Wall -Werror -Wextra

SRCS = srcs/main.c 
OBJS = $(SRCS:.c=.o)

INCLUDES_DIR = includes

LIBFT_DIR = libft
LIBFT = libft/libft.a

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	cc $(CFLAGS) $(OBJS) -L $(LIBFT_DIR) -lft -o $@

$(LIBFT):
	make -C $(LIBFT_DIR)

%.o: %.c
	cc $(CFLAGS) -I $(INCLUDES_DIR) -I $(LIBFT_DIR) $< -o $@

clean:
	make clean -C $(LIBFT_DIR)
	rm -f $(OBJS)

fclean: clean
	make fclean -C $(LIBFT_DIR)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

