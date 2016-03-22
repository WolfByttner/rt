/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbyttner <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/21 19:38:41 by jbyttner          #+#    #+#             */
/*   Updated: 2016/03/22 18:05:37 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*static t_params	*init_params(int ac, char **av)
{
	static t_params		a = {{512, 512}};
	int					i;

	if (ac <= 0)
		return (&a);
	i = -1;
	while (++i < ac)
		if (!ft_strcmp(av[i], "-res"))
			if (ac - i - 1 < 2)
				err("-res: not enough parameters\n");
			else
			{
				a.res[0] = ft_atoi(av[++i]);
				a.res[1] = ft_atoi(av[++i]);
				if (a.res[0] < 1 || a.res[1] < 1)
					err("-res: only res > 1 allowed\n");
			}
	return (&a);
}*/

int				main(void)
{
	GLFWwindow			*window;
	int					i;
	static const float	verts[] = {-0.5f, 0.5f, -0.5f, -0.5f, 0.5f, -0.5f, 0.5f, 0.5f};
	static const int	inds[] = {0, 1, 3, 1, 2, 3};

	if (!glfwInit())
		err("GLFW failed to init\n");
	glfwWindowHint(GLFW_RESIZABLE, 0);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	window = glfwCreateWindow(1000, 1000, P_NAME, 0, 0);
	if (!window)
	{
		glfwTerminate();
		err("GLFW failed to create window");
	}
	glfwMakeContextCurrent(window);
	glfwSwapInterval(0);
	i = -1;
	glClearColor(0, 1, 0, 1);
	GLuint model = vao();
	GLuint v = data_buffer((GLvoid*)verts, sizeof(verts)/sizeof(float));
	GLuint in = index_buffer((GLvoid*)inds, sizeof(inds)/sizeof(int));
	vao_add_indices(model, in);
	vao_add_vdata(model, v, 2, 0);
	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glBindVertexArray(model);
		glEnableVertexAttribArray(0);
		glDrawElements(GL_TRIANGLES, sizeof(inds)/sizeof(int), GL_UNSIGNED_INT, 0);
		glDisableVertexAttribArray(0);
	ft_putnbr(glGetError());
	ft_putendl("");
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glDeleteVertexArrays(1, &model);
	glDeleteBuffers(1, &v);
	glDeleteBuffers(1, &in);
	glfwTerminate();
	return (0);
}
