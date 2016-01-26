# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fnieto <fnieto@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2013/11/19 14:09:58 by apachkof          #+#    #+#              #
#    Updated: 2016/01/18 20:01:42 by fnieto           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=fred_gl.a

CC=gcc

CFLAGS=-Wall -Wextra -Werror -O3

RM=rm -f

SRC=div_vec2.c gl_lines.c mix_vec3.c smoothstep_vec2.c vec3.c add_vec2.c div_vec3.c lerp_vec2.c mix_vec4.c smoothstep_vec3.c vec4.c add_vec3.c div_vec4.c lerp_vec3.c mul_mat4.c smoothstep_vec4.c vertex.c add_vec4.c encoder.c lerp_vec4.c mul_vec2.c sub_vec2.c buffer.c frame.c mul_vec3.c sub_vec3.c converter.c fred_gl.c mat4.c mul_vec4.c sub_vec4.c decoder.c mix_vec2.c projection.c vec2.c len_vec2.c len_vec3.c len_vec4.c gl_matrix.c gl_vertex.c gl_vertex_2.c time.c

OBJ=$(SRC:.c=.o)

INCL=../libft/includes/

$(NAME): fred_gl.h
		$(CC) $(CFLAGS) -c $(SRC) -I $(INCL)
		ar rc $(NAME) $(OBJ)
		ranlib $(NAME)

all: $(NAME)

clean:
		$(RM) $(OBJ)

fclean: clean
		$(RM) $(NAME)

re: fclean all

.PHONY: clean fclean
