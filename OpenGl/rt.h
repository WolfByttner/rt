/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbyttner <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/21 19:50:48 by jbyttner          #+#    #+#             */
/*   Updated: 2016/03/22 16:43:07 by jbyttner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H
# include <GLFW/glfw3.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "libft.h"
# define P_NAME "foobar"
# define BUFF_LENGTH 100

void				err(char *msg);
void				load_file(char *file, GLchar **ptr, GLint *length);
GLuint				shader(GLenum t, GLsizei c, GLchar **s, GLint *l);
GLuint				shader_program(GLuint *shaders, size_t size);

#endif
