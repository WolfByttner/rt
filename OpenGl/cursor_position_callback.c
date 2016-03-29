/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_position_callback.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbyttner <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/29 21:51:02 by jbyttner          #+#    #+#             */
/*   Updated: 2016/03/29 22:07:39 by jbyttner         ###   ########.fr       */
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
	u->camrot[1] += (xpos - xold) * u->camsr;
	u->camrot[0] += (ypos - yold) * u->camsr;
	printf ("rotating by %f| %f\n", u->camrot[1], u->camrot[0]);
	glUniform2f(u->icamrot, u->camrot[0], u->camrot[1]);
	xold = xpos;
	yold = ypos;
}
