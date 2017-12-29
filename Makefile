#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: skavunen <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/01/12 12:37:31 by skavunen          #+#    #+#              #
#    Updated: 2017/04/17 13:39:17 by okovalov         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = wolf3d

SRC = 	main.c \
		clc.c \
		wolf.c \
		key.c \

OBJ = $(SRC:.c=.o)

CC = gcc

FLGS = -Wall -Wextra -Werror

INC = ./

LIB = -L ./libft/ -lft

all: $(NAME)

$(NAME): $(OBJ)
		make -C ./libft/
		$(CC) -o $(NAME) $(OBJ) $(LIB) -lmlx -framework OpenGL -framework AppKit

%.o: %.c
		$(CC) $(FLGS) -c $<

clean:
		make -C ./libft/ clean
		rm -rf $(OBJ)

fclean: clean
		make -C ./libft/ fclean
		rm -f $(NAME)

re: fclean all