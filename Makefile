CC = cc
NAME = fdf
PREFIX = 
COMPILE_FLAGS = -Wall -Wextra -Werror
LINK_MINILIBX_FLAGS = -lmlx -lXext -lX11 -Lminilibx-linux
LINK_LIBFT_FLAGS = -lft -Llibft
LINK_OTHER_FLAGS = -lm
INCLUDES = -Ilibft -Iminilibx-linux

all: $(NAME)

pre: 
	$(PREFIX)cd libft && make all && cd ../minilibx-linux && make all

SRCS = utils.c controls.c map_reading.c draw.c transform.c map_limits.c line.c line_math.c line_endpoint.c line_pixel.c
OBJS = $(SRCS:.c=.o)

ENDPOINT_SRCS = main.c
ENDPOINT_OBJS = $(ENDPOINT_SRCS:.c=.o)

$(NAME): pre $(OBJS) $(ENDPOINT_OBJS)
	$(PREFIX)$(CC) $(OBJS) $(ENDPOINT_OBJS) -o $@ $(LINK_LIBFT_FLAGS) $(LINK_MINILIBX_FLAGS) $(LINK_OTHER_FLAGS)

$(OBJS): %.o: %.c
	$(PREFIX)$(CC) $(COMPILE_FLAGS) $< -o $@ -g $(INCLUDES) -c

$(ENDPOINT_OBJS): %.o: %.c
	$(PREFIX)$(CC) $(COMPILE_FLAGS) $< -o $@ -g $(INCLUDES) -c

preclean:
	$(PREFIX)cd libft && make clean
	$(PREFIX)cd minilibx-linux && make clean

prefclean:
	$(PREFIX)cd libft && make fclean
	$(PREFIX)cd minilibx-linux && make clean

clean: preclean
	$(PREFIX)rm -f $(OBJS) $(ENDPOINT_OBJS)

fclean: clean prefclean
	$(PREFIX)rm -f $(NAME)

re: fclean all

PHONY: all pre preclean clean fclean re
