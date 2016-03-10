/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 21:44:02 by fnieto            #+#    #+#             */
/*   Updated: 2016/03/10 03:25:48 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <GLFW/glfw3.h>
#include "rt.h"

static t_params	init_params(int ac, char **av)
{
	static t_params a = {0};

	ac = 0;
	*av = 0;
	return (a);
}

int				main(int ac, char **av)
{
	GLFWwindow		*window;

	if (!glfwInit())
		return (-1);
	window = glfwCreateWindow(640, 480, PROJ_NAME, NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return (-1);
	}
	glfwMakeContextCurrent(window);
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	return (0);
}
