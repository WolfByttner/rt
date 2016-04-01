/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbyttner <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/21 19:38:41 by jbyttner          #+#    #+#             */
/*   Updated: 2016/04/01 14:37:51 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "rt_input.h"
#include <sys/time.h>
#include <stdio.h>
#define FOO 1

static t_properties		*get_properties(void)
{
	static t_properties properties;

	return (&properties);
}

static void window_size_callback(GLFWwindow* window, int width, int height)
{
	t_properties *props;

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
	//glfwWindowHint(GLFW_RESIZABLE, 0);
	//glfwWindowHint(GLFW_DECORATED, 0);
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

int					main(void)
{
	GLFWwindow			*window;
	int					i;
	t_properties		*properties;
	static const float	verts[] = {-FOO, FOO,
					-FOO, -FOO,
					FOO, -FOO,
					FOO, FOO};
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
	ft_putendl(" 0");

	GLint sizes[2];
	GLchar *srcs[2];
	load_file("vertex.c", srcs, sizes);
	load_file("fragment.c", &(srcs[1]), &(sizes[1]));
	GLuint shaders[2];
	shaders[0] = shader(GL_VERTEX_SHADER, 1, &(srcs[0]), &(sizes[0]));
	shaders[1] = shader(GL_FRAGMENT_SHADER, 1, &(srcs[1]), &(sizes[1]));
	GLuint program = shader_program(shaders, 2);
	GLint ires = glGetUniformLocation(program, "iResolution");
	GLint itime = glGetUniformLocation(program, "iGlobalTime");
	ft_putnbr(glGetError());
	ft_putendl(" 1");

	struct timeval tval;
	gettimeofday(&tval, 0);
	long t = tval.tv_sec * 1e6 + tval.tv_usec;
	long st = t;
	long t2 = t;
	long told = t;
	int fps = 0;

	glUseProgram(program);
	glBindVertexArray(model);
	glEnableVertexAttribArray(0);
	init_uniforms(program);
	glfwSetCursorPosCallback(window, cursor_position_callback);
	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glUniform2i(ires, properties->width, properties->height);
		glUniform1f(itime, (float)((double)(t2 - st) / 1000000.0f));
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);
		glfwPollEvents();
		++fps;
		gettimeofday(&tval, 0);
		if ((t2 = tval.tv_sec * 1e6 + tval.tv_usec) > t + 1000000)
		{
			printf("%i\n", fps);
			t = t2;
			fps = 0;
		}
		poll_keys(window, (float)(t2 - told) / 1000000.0f);
		told = t2;
	}
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
