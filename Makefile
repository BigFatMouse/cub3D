NAME = cub3D
HEADER = cub.h
CC = gcc
FLAGS = -Wall -Wextra -Werror 
OPTIONS = -Lmlx -lmlx -framework OpenGL -framework AppKit
SRC =  srcs/parser1.c srcs/pars_funcs.c srcs/parcer.c \
	srcs/cub.c \
	srcs/keyhooks.c srcs/screenshot.c \
	srcs/mlx_func.c srcs/put_sprites.c srcs/sort_sprites.c \
	
OBJ = $(SRC:%.c=%.o)


all: $(NAME)
	
$(NAME): $(OBJ)
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
