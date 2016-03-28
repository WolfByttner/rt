/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbyttner <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/21 19:38:41 by jbyttner          #+#    #+#             */
/*   Updated: 2016/03/28 02:02:00 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <time.h>
#include <stdio.h>
#define FOO 1

static GLFWwindow	*make_glfw(int width, int height)
{
	GLFWwindow			*window;

	if (!glfwInit())
		err("GLFW failed to init\n");
	glfwWindowHint(GLFW_RESIZABLE, 0);
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
	glfwMakeContextCurrent(window);
	glfwSwapInterval(0);
	return (window);
}

int					main(void)
{
	GLFWwindow			*window;
	int					i;
	static const float	verts[] = {-FOO, FOO,
					-FOO, -FOO,
					FOO, -FOO,
					FOO, FOO};
	static const GLuint	inds[] = {0, 1, 3, 1, 2, 3};

	window = make_glfw(1000, 1000);
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
	GLint itime = glGetUniformLocation(program, "iGlobalTimeTime");
	ft_putnbr(glGetError());
	ft_putendl(" 1");
	time_t t = time(0);
	int t2;
	int fps = 0;
	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(program);
		glUniform2i(ires, 1000, 1000);
		glUniform1f(itime, (float)((double)(clock()) / .5e6));
		glBindVertexArray(model);
		glEnableVertexAttribArray(0);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);
		glfwPollEvents();
		++fps;
		if ((t2 = time(0)) > t)
		{
			printf("%i\n", fps);
			t = t2;
			fps = 0;
		}
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
