/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbyttner <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/21 19:50:48 by jbyttner          #+#    #+#             */
/*   Updated: 2016/04/27 21:55:52 by jbyttner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Include in CPU code
*/

#ifndef RT_H
# define RT_H
# define GLFW_INCLUDE_GLCOREARB
# if defined __apple__ || defined APPLE
#  include <OpenGL/gl3.h>
# elif defined __linux__ || defined LINUX
#  define GL_GLEXT_PROTOTYPES 0
# else
#  error Unknow architecture
# endif
# include <GLFW/glfw3.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "libft.h"

# define P_NAME "foobar"
# define BUFF_LENGTH 1

typedef	struct		s_properties
{
	int		width;
	int		height;
	GLuint	model;
	GLuint	verts;
	GLuint	indices;
	GLuint	shaders[2];
	GLuint	program;
	GLint	ires;
	GLint	itime;
}					t_properties;

void				err(char *msg);

void				load_file(char *file, GLchar **ptr, GLint *length);

GLuint				load_fragment(void);

GLuint				shader(GLenum t, GLsizei c, GLchar **s, GLint *l);

GLuint				shader_program(GLuint *shaders, size_t size);

GLuint				vao(void);

void				main_loop(GLFWwindow *window, t_properties *properties);

GLFWwindow			*setup_program(t_properties *properties);

void				poll_keys(GLFWwindow *window, float ftime);

void				vao_add_indices(GLuint vao, GLuint vbo);

void				vao_add_vdata(GLuint vao, GLuint vbo, GLint s, GLboolean n);

t_properties		*get_properties(void);

GLuint				vbo(GLenum t, GLsizeiptr s, GLvoid *d, GLenum u);

GLuint				index_buffer(GLvoid *d, GLsizeiptr s);

GLuint				data_buffer(GLvoid *d, GLsizeiptr s);

#endif
