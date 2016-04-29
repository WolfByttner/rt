/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_program.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbyttner <jbyttner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/27 21:38:37 by jbyttner          #+#    #+#             */
/*   Updated: 2016/04/29 19:32:00 by jbyttner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "rt_input.h"

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

GLFWwindow			*setup_program(t_properties *properties)
{
	static const float	verts[] = {-1, 1, -1, -1, 1, -1, 1, 1};
	static const GLuint	inds[] = {0, 1, 3, 1, 2, 3};
	GLFWwindow			*window;

	properties->width = 1000;
	properties->height = 1000;
	window = make_glfw(properties->width, properties->height);
	glClearColor(0, 0, 0, 1);
	properties->model = vao();
	properties->verts = data_buffer((GLvoid *)verts, sizeof(verts));
	properties->indices = index_buffer((GLvoid *)inds, sizeof(inds));
	vao_add_indices(properties->model, properties->indices);
	vao_add_vdata(properties->model, properties->verts, 2, GL_FALSE);
	ft_putnbr(glGetError());
	ft_putendl(" -0");
	properties->shaders[0] = load_vertex();
	properties->shaders[1] = load_fragment(properties->map);
	properties->program = shader_program(properties->shaders, 2);
	ft_putnbr(glGetError());
	ft_putendl(" -1");
	glUseProgram(properties->program);
	glBindVertexArray(properties->model);
	glEnableVertexAttribArray(0);
	init_uniforms(properties->program);
	return (window);
}
