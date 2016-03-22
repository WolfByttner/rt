# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fnieto <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/03/09 20:50:44 by fnieto            #+#    #+#              #
#    Updated: 2016/03/22 11:21:47 by fnieto           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=rt

CC=gcc

CFLAGS= -Wall -Wextra -Werror

RM=rm -f

SRC=main.c\
	err.c\
	shader.c\

LIB=-L ~/.brew/Cellar/glfw3/3.1.2/lib/ -lglfw3 -framework OpenGL

INCL=-I ~/.brew/Cellar/glfw3/3.1.2/include/ -I .

OBJ=$(SRC:.c=.o)

$(NAME): $(OBJ) $(NAME).h
	@$(CC) -o $(NAME) $(OBJ) $(LIB) $(CFLAGS)
	@echo "[.o] >> [rt]"

%.o: %.c
	@-$(CC) $(INCL) -c $< -o $@ $(CFLAGS)
	@echo "$< >> $@"

all: $(NAME)

announce_name:
	@echo "Making $(NAME)"

norm:
	@norminette $(SRC) $(NAME).h

clean:
	@$(RM) $(OBJ)
	@echo "[.o] >> /dev/null"

fclean: clean
	@$(RM) $(NAME)
	@echo "[rt] >> /dev/null"

re: fclean all

.PHONY: clean fclean
