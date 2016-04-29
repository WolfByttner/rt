# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fnieto <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/03/09 20:50:44 by fnieto            #+#    #+#              #
#    Updated: 2016/04/28 19:51:32 by mdeken           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=rt

CC=gcc

CFLAGS= -Wall -Wextra -Werror

RM=rm -f

SRC=main.c\
	main_loop.c\
	setup_program.c\
	err.c\
	shader.c\
	vao.c\
	vbo.c\
	load_file.c\
	load_fragment.c\
	get_properties.c\
	poll_keys.c\
	init_uniforms.c\
	get_uniforms.c\
	cursor_position_callback.c\
	window_size_callback.c

UNAME := $(shell uname)
ifeq ($(UNAME), Linux)
  LIB= -lglfw libft/libft.a -lm -lGL 
  INCL=-I libft/includes
  CFLAGS += -D LINUX
else
  LIB=-L ~/.brew/Cellar/glfw3/3.1.2/lib/ -lglfw3 -framework OpenGL libft/libft.a
  INCL=-I ~/.brew/Cellar/glfw3/3.1.2/include/ -I . -I libft/includes
  CFLAGS += -D APPLE
endif

OBJ=$(SRC:.c=.o)

$(NAME): $(OBJ) $(NAME).h
	@echo "Compiling for " $(UNAME)
	@make -C libft
	@echo "[>>libft<<]"
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
	@make -C libft/ clean
	@$(RM) $(OBJ)
	@echo "[.o] >> /dev/null"

fclean: clean
	@make -C libft/ fclean
	@$(RM) $(NAME)
	@echo "[rt] >> /dev/null"

re: fclean all

.PHONY: clean fclean
