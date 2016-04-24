/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbyttner <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/21 19:38:41 by jbyttner          #+#    #+#             */
/*   Updated: 2016/04/24 16:54:17 by fnieto           ###   ########.fr       */
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

GLuint				load_vertex(void)
{
	static GLchar	*src = ("#version 330 core\nlayout(location=0)in vec2 pos;"
	
	"void main(){gl_Position.xy = pos;}");
	return (shader(GL_VERTEX_SHADER, 1, &src, 0));
}

GLchar				*get_frag_params(void)
{
	static GLchar	*src = ("uniform ivec2 iResolution;\n"

	"uniform vec3 iCameraPosition = vec3(0, 0, 0);\n"
	"uniform vec2 iCameraRotation = vec2(0, 0);\n"
	"uniform float iCameraZoom = 1;\n"
	"uniform float iGlobalTime = 0;\n"
	"layout (location = 0) out vec4 outcol;\n");
	return (src);
}

void				printsrc(GLchar **src, int size)
{
	int	i;

	i = -1;
	while (++i < size)
		ft_putstr(src[i]);
}

GLuint				load_fragment(void)
{
	GLint sizes[15];
	GLchar *srcs[15];

	load_file("fragment.h", &(srcs[0]), &(sizes[0]));
	srcs[0] = ft_strjoin("#version 330 core\n", srcs[0]);
	sizes[0] += 18;
	srcs[1] = get_frag_params();
	sizes[1] = 0;
	load_file("shader_default_map", &(srcs[2]), &(sizes[2]));
	load_file("shader_iterate.c", &(srcs[3]), &(sizes[3]));
	load_file("shader_paint.c", &(srcs[4]), &(sizes[4]));
	load_file("shader_render_lights.c", &(srcs[5]), &(sizes[5]));
	load_file("shader_raytrace.c", &(srcs[6]), &(sizes[6]));
	load_file("shader_mobius.c", &(srcs[7]), &(sizes[7]));
	load_file("shader_box.c", &(srcs[8]), &(sizes[8]));
	load_file("shader_cone.c", &(srcs[9]), &(sizes[9]));
	load_file("shader_cylinder.c", &(srcs[10]), &(sizes[10]));
	load_file("shader_ellipse.c", &(srcs[11]), &(sizes[11]));
	load_file("shader_plane.c", &(srcs[12]), &(sizes[12]));
	load_file("shader_sphere.c", &(srcs[13]), &(sizes[13]));
	load_file("shader_main.c", &(srcs[14]), &(sizes[14]));
	printsrc(srcs, 15);
	return (shader(GL_FRAGMENT_SHADER, 15, srcs, 0));
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
