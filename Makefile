NAME = cub3D
SRC = cub.c parcer.c
HEADER = cub3d.h
OBJ = $(SRC:%.c=%.o)
CC = gcc
FLAGS = -Wall -Wextra -Werror 
OPTIONS = -Lmlx -lmlx -framework OpenGL -framework AppKit


all: $(NAME)
	
$(NAME): $(OBJ) 
	make -C mlx/
	make -C libft/
	$(CC) -g $(FLAGS) $(OPTIONS) $(OBJ) libft/libft.a -o $(NAME)
	

%.o: %.c $(HEADER)
	$(CC) $(FLAGS) -Imlx -c $< -o $@
	
clean:
	rm -rf $(OBJ)
	make clean -C libft/

fclean: clean
	rm -rf $(NAME)
	make fclean -C libft/

re: fclean all

.PHONY: all clean fclean re
