/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbyttner <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/21 19:38:41 by jbyttner          #+#    #+#             */
/*   Updated: 2016/03/21 20:19:36 by jbyttner         ###   ########.fr       */
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

int				main(int ac, char **av)
{
	GLFWwindow		*window;
	int				i;

	if (!glfwInit())
		err("GLFW failed to init\n");
	glfwWindowHint(GLFW_RESIZABLE, 0);
	window = glfwCreateWindow(1000, 1000, P_NAME, 0, 0);
	if (!window)
	{
		glfwTerminate();
		err("GLFW failed to create window");
	}
	glfwMakeContextCurrent(window);
	glfwSwapInterval(0);
	i = -1;
	glClearColor(0, 0, 0, 1);
	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glBegin(GL_QUADS);
		glColor4f(1, 1, 1, 1);
		glVertex2f(-1, -1);
		glVertex2f(1, -1);
		glVertex2f(1, 1);
		glVertex2f(-1, 1);
		glEnd();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	return (0);
}
