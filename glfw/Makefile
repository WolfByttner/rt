# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fnieto <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/03/09 20:50:44 by fnieto            #+#    #+#              #
#    Updated: 2016/03/10 22:43:13 by fnieto           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=rt

CC=/Developer/NVIDIA/CUDA-7.5/bin/nvcc

CFLAGS= -w

RM=rm -f

SRC=main.c\
	cudasync.c\
	t_float_add.c\
	t_float_cross.c\
	t_float_div.c\
	t_float_dot.c\
	t_float_mul.c\
	t_float_reflect.c\
	t_float_set.c\
	t_float_setv.c\
	t_float_sub.c\
	err.c\
	ft_atoi.c\
	test_kernel.c

LIB=-L ~/.brew/Cellar/glfw3/3.1.2/lib/ -lglfw3 -Xlinker -framework,Cocoa,-framework,OpenGL,-framework,IOKit,-framework,CoreVideo

INCL=-I ~/.brew/Cellar/glfw3/3.1.2/include/ -I .

OBJ=$(SRC:.c=.o)

$(NAME): $(OBJ) $(NAME).h
	@$(CC) -o $(NAME) $(OBJ) $(LIB) $(CFLAGS)
	@echo "[.o] >> [rt]"

%.o: %.c
	@mv $< $(<:.c=.cu)
	@-$(CC) $(INCL) -c $(<:.c=.cu) -o $@ $(CFLAGS)
	@mv $(<:.c=.cu) $<
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
