NAME = cub3D
SRC = main.c
HEADER = cub3d.h
OBJ = $(SRC:%.c=%.o)
CC = gcc
FLAGS = -Wall -Wextra -Werror 
OPTIONS = -Lmlx -lmlx -framework OpenGL -framework AppKit


all: $(NAME)
	
$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OPTIONS) $(OBJ) -o $(NAME)
	make -C mlx

%.o: %.c $(HEADER)
	$(CC) $(FLAGS) -Imlx -c $< -o $@
	
clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
