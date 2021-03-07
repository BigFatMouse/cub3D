# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mhogg <mhogg@student.21-school.ru>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/07 16:06:33 by mhogg             #+#    #+#              #
#    Updated: 2021/03/07 21:15:37 by mhogg            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
SRC = ft_atof_move.c ft_atoi_move.c ft_strlen.c ft_strcpy.c ft_strchr.c  \
ft_isdigit.c ft_substr.c ft_strtrim.c ft_lstnew.c ft_lstadd_front.c ft_strjoin.c \
ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c get_next_line.c
OBJ = $(SRC:%.c=%.o)
BOBJ = $(BSRC:%.c=%.o)
CC = gcc
FLAGS = -Wall -Wextra -Werror

all: $(NAME)
	
$(NAME): $(OBJ)
	ar -rcs $(NAME) $(OBJ)

%.o: %.c 
	$(CC) $(FLAGS) -c $< -o $@

bonus: $(OBJ) $(BOBJ)
	ar -rcs $(NAME) $(OBJ) $(BOBJ)

clean:
	rm -rf $(OBJ) $(BOBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all
