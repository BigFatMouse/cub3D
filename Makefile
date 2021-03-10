NAME = cub3D
SRC = cub.c parcer.c
HEADER = cub.h
OBJ = $(SRC:%.c=%.o)
CC = gcc
FLAGS = -Wall -Wextra -Werror 
OPTIONS = -Lmlx -lmlx -framework OpenGL -framework AppKit

all: $(NAME)
	
$(NAME): $(OBJ)
	make -C mlx/
	cp mlx/libmlx.dylib .
	make -C libft/
	$(CC) $(OPTIONS) $(OBJ) libft/libft.a -o $(NAME)

%.o: %.c $(HEADER)
	$(CC) -Imlx -c $< -o $@
	
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
