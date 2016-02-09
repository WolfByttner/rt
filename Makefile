# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fnieto <fnieto@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2013/11/19 14:09:58 by apachkof          #+#    #+#              #
#    Updated: 2016/02/09 23:42:42 by fnieto           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=rt

CC=gcc

CFLAGS=-Wall -Wextra -Werror -O3

RM=rm -f

SRC=main.c clutil.c shaderutil.c

LIB= -framework OpenGL -framework AppKit libft/libft.a minilibx_macos/libmlx.a fred_gl/fred_gl.a -framework OpenCL

INCL=-I libft/includes/ -I minilibx_macos/ -I fred_gl/

OBJ=$(SRC:.c=.o)

$(NAME): $(OBJ)
		make -C libft/
		make -C fred_gl/
		$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(INCL) $(LIB)

%.o: %.c
		$(CC) $(CFLAGS) $(INCL) -c $< -o $@

all: $(NAME)

clean:
		$(RM) $(OBJ)

fclean: clean
		$(RM) $(NAME)

re: fclean all

.PHONY: clean fclean
