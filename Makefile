NAME = cub3D
HEADER = cub.h
LIB_HEADER = libft/libft.h
CC = gcc
FLAGS = -Wall -Wextra -Werror 
OPTIONS = -Lmlx -lmlx -framework OpenGL -framework AppKit
SRC =  srcs/parser1.c srcs/parser2.c srcs/parser3.c \
		srcs/parser4.c srcs/pars_funcs.c srcs/keyhooks.c \
		srcs/cub_funcs.c srcs/put_scene1.c \
		srcs/put_scene2.c srcs/screenshot.c srcs/mlx_func.c \
		srcs/put_sprites.c srcs/sort_sprites.c srcs/main.c \
	
OBJ = $(SRC:%.c=%.o)

all: $(NAME)
	
$(NAME): $(OBJ) $(HEADER) $(LIB_HEADER)
	make -C mlx/
	cp mlx/libmlx.dylib .
	make -C libft/
	$(CC) $(FLAGS) $(OPTIONS) $(OBJ) libft/libft.a -o $(NAME)

/%.o: %.c $(HEADER) 
	$(CC) $(FLAGS) -Imlx -c $< -o $@
	
clean:
	rm -rf $(OBJ)
	make clean -C mlx/
	make clean -C libft/

fclean: clean
	rm -rf $(NAME)
	make fclean -C libft/
	rm -rf mlx/libmlx.dylib
	rm -rf libmlx.dylib

re: fclean all

.PHONY: all clean fclean re
