CC = cc
NAME = fdf
PREFIX = 
COMPILE_FLAGS = -Wall -Wextra -Werror
LINK_MINILIBX_FLAGS = -lmlx -lXext -lX11 -Lminilibx-linux
LINK_LIBFT_FLAGS = -lft -Llibft
INCLUDES = -Ilibft -Iminilibx-linux

all: $(NAME)

pre: cd libft && make all && cd ../minilibx-linux && make all

SRCS = main.c
OBJS = $(SRCS:.c=.o)

$(NAME): $(OBJS)
	$(PREFIX)$(CC) $< -o $@ $(LINK_LIBFT_FLAGS) $(LINK_MINILIBX_FLAGS)

$(OBJS): %.o: %.c
	$(PREFIX)$(CC) $(COMPILE_FLAGS) $< -o $@ -g $(INCLUDES) -c

preclean:
	$(PREFIX)cd libft && make clean
	$(PREFIX)cd minilibx-linux && make clean

prefclean:
	$(PREFIX)cd libft && make fclean
	$(PREFIX)cd minilibx-linux && make fclean

clean:
	$(PREFIX)rm -f $(OBJS) 

fclean:
	$(PREFIX)rm -f $(NAME)

re: fclean all

PHONY: all pre preclean clean fclean re
