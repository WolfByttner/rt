# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mwilk <mwilk@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/11/09 16:17:56 by mwilk             #+#    #+#              #
#    Updated: 2016/03/08 22:11:20 by mwilk            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


## PROJECT

NAME = RT

LIBFT = libft

## COMPILATEUR

OS = $(shell uname -s)
CC = clang
FLAGS = -Wall -Wextra -Werror

## FILES

SRC = main.c\

INC =  -I ./
INC += -I ./SDL2/include/SDL2/

OBJ = $(SRC:.c=.o)

LIB = -L `sdl2-config --cflags --libs` -lSDL2

## RULES

all: $(NAME)

update:
	git pull
	git submodule update --init --recursive
	git submodule foreach git pull origin master

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(INC) $(LIB) -o $(NAME) $(SRC)
	@echo "\033[35m <(O.O<) WOW ! Very $(NAME) ! Amaze ! (>^o^)> \033[0m"

clean:
	rm -rf $(OBJ)
	@echo "\033[36mT.T Miss you $(NAME)-object files T.T \033[0m"

fclean:
	rm -rf $(OBJ)
	@echo "\033[36mT.T Miss you $(NAME)-object files T.T \033[0m"
	rm -rf $(NAME)
	@echo "\033[36m X.x Bye Bye $(NAME)-compiled files >_< \033[0m"

%.o:%.c
	@echo "<(O.o)>\t\t$@\t\t<(o.O)>"
	@$(CC) $(FLAGS) $(INC) -c $< -o $@

re: fclean all

.PHONY: all normal clean fclean re

