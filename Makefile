CC = cc
NAME = fdf
PREFIX = 
COMPILE_FLAGS = -Wall -Wextra -Werror
LINK_MINILIBX_FLAGS = -lmlx -lXext -lX11 -Lminilibx-linux
LINK_LIBFT_FLAGS = -lft -Llibft

all: $(NAME)

PRE: cd libft && make all && cd ../minilibx-linux && make all

SRCS = main.c
OBJS = $(SRCS)

$(NAME): #PRE
	$(PREFIX)$(CC) $(COMPILEFLAGS) 
