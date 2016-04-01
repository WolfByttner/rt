/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_position_callback.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbyttner <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/29 21:51:02 by jbyttner          #+#    #+#             */
/*   Updated: 2016/04/01 15:53:01 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_input.h"
#include <stdio.h>

void	cursor_position_callback(GLFWwindow *window, double xpos, double ypos)
{
	static double	xold;
	static double	yold;
	t_uniforms		*u;

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); // TODO: Move this (and use window);
	u = get_uniforms();
	u->camrot[0] += (xpos - xold) * u->camsr;
	u->camrot[1] += (ypos - yold) * u->camsr;
	if (u->camrot[1] > 1.57079632679)
		u->camrot[1] = 1.57079632679;
	else if (u->camrot[1] < -1.57079632679)
		u->camrot[1] = -1.57079632679;
	printf ("rotating by %f| %f\n", u->camrot[1], u->camrot[0]);
	glUniform2f(u->icamrot, u->camrot[0], u->camrot[1]);
	xold = xpos;
	yold = ypos;
}
