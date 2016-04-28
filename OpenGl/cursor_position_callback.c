/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_position_callback.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbyttner <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/29 21:51:02 by jbyttner          #+#    #+#             */
/*   Updated: 2016/04/28 19:15:59 by mdeken           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_input.h"
#include <stdio.h>

void	cursor_position_callback(GLFWwindow *window, double xpos, double ypos)
{
	static double	xold;
	static double	yold;
	t_uniforms		*u;

	u = get_uniforms();
	if (u->mouse_moving == 1)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		u->camrot[0] += (xpos - xold) * u->camsr;
		u->camrot[1] += (ypos - yold) * u->camsr;
		if (u->camrot[1] > 1.57079632679)
			u->camrot[1] = 1.57079632679;
		else if (u->camrot[1] < -1.57079632679)
			u->camrot[1] = -1.57079632679;
		glUniform2f(u->icamrot, u->camrot[0], u->camrot[1]);
		xold = xpos;
		yold = ypos;
	}
	else
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}
