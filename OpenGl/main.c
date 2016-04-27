/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbyttner <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/21 19:38:41 by jbyttner          #+#    #+#             */
/*   Updated: 2016/04/27 20:24:35 by jbyttner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "rt_input.h"
#include <sys/time.h>
#include <stdio.h>

static t_properties	*get_properties(void)
{
	static t_properties	properties;

	return (&properties);
}

static void			window_size_callback(GLFWwindow *window,
						int width, int height)
{
	t_properties		*props;

	props = get_properties();
	props->width = width;
	props->height = height;
	window = 0;
}

static GLFWwindow	*make_glfw(int width, int height)
{
	GLFWwindow			*window;

	if (!glfwInit())
		err("GLFW failed to init\n");
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	window = glfwCreateWindow(width, height, P_NAME, 0, 0);
	if (!window)
	{
		glfwTerminate();
		err("GLFW failed to create window");
	}
	glfwSetWindowSizeCallback(window, window_size_callback);
	glfwMakeContextCurrent(window);
	glfwSwapInterval(0);
	return (window);
}

GLuint				load_vertex(void)
{
	static GLchar		*src = ("#version 330 core\n"

	"layout(location=0)in vec2 pos;"
	"void main(){gl_Position.xy = pos;}");
	return (shader(GL_VERTEX_SHADER, 1, &src, 0));
}

int					main(void)
{
	GLFWwindow			*window;
	int					i;
	t_properties		*properties;
	static const float	verts[] = {-1, 1, -1, -1, 1, -1, 1, 1};
	static const GLuint	inds[] = {0, 1, 3, 1, 2, 3};

	properties = get_properties();
	properties->width = 1000;
	properties->height = 1000;
	window = make_glfw(properties->width, properties->height);
	i = -1;
	glClearColor(0, 0, 0, 1);
	GLuint model = vao();
	GLuint v = data_buffer((GLvoid*)verts, sizeof(verts));
	GLuint in = index_buffer((GLvoid*)inds, sizeof(inds));
	vao_add_indices(model, in);
	vao_add_vdata(model, v, 2, GL_FALSE);
	ft_putnbr(glGetError());
	ft_putendl(" -0");

	GLuint shaders[2];
	shaders[0] = load_vertex();
	shaders[1] = load_fragment();
	GLuint program = shader_program(shaders, 2);
	GLint ires = glGetUniformLocation(program, "iResolution");
	GLint itime = glGetUniformLocation(program, "iGlobalTime");
	ft_putnbr(glGetError());
	ft_putendl(" -1");
	glUseProgram(program);
	glBindVertexArray(model);
	glEnableVertexAttribArray(0);
	init_uniforms(program);
	glfwSetCursorPosCallback(window, cursor_position_callback);
	main_loop(window, ires, itime, properties);
	ft_putnbr(glGetError());
	ft_putendl(" 2");
	glDeleteShader(shaders[0]);
	glDeleteShader(shaders[1]);
	glDeleteProgram(program);
	glDeleteVertexArrays(1, &model);
	glDeleteBuffers(1, &v);
	glDeleteBuffers(1, &in);
	glfwTerminate();
	return (0);
}
