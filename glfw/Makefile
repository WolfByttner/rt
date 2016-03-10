# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fnieto <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/03/09 20:50:44 by fnieto            #+#    #+#              #
#    Updated: 2016/03/10 03:12:29 by fnieto           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=rt

CC=/Developer/NVIDIA/CUDA-7.5/bin/nvcc

CFLAGS=-Xptxas -Werror -m64

RM=rm -f

SRC=main.c cudasync.c

LIB=-L ~/.brew/Cellar/glfw3/3.1.2/lib/ -lglfw3 -Xlinker -framework,Cocoa,-framework,OpenGL,-framework,IOKit,-framework,CoreVideo

INCL=-I ~/.brew/Cellar/glfw3/3.1.2/include/ -I .

OBJ=$(SRC:.c=.o)

$(NAME): $(OBJ)
	@$(CC) -o $(NAME) $(OBJ) $(LIB) $(CFLAGS)
	@echo "[.o] >> [rt]"

%.o: %.c
	@mv $< $(<:.c=.cu)
	@-$(CC) $(INCL) -c $(<:.c=.cu) -o $@ $(CFLAGS)
	@mv $(<:.c=.cu) $<
	@echo "$< >> $@"

all: $(NAME)

clean:
	@$(RM) $(OBJ)
	@echo "[.o] >> /dev/null"

fclean: clean
	@$(RM) $(NAME)
	@echo "[rt] >> /dev/null"

re: fclean all

.PHONY: clean fclean
