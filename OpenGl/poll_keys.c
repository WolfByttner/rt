/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   poll_keys.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbyttner <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/29 20:50:54 by jbyttner          #+#    #+#             */
/*   Updated: 2016/03/29 21:12:42 by jbyttner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_input.h"

static void	poll_movement_keys(GLFWwindow *window, float ftime, t_uniforms *u)
{
	int		state;

	if ((state = glfwGetKey(window, GLFW_KEY_W)) == GLFW_PRESS)
		u->campos[0] += u->cammov * ftime;
	else if ((state = glfwGetKey(window, GLFW_KEY_S)) == GLFW_PRESS)
		u->campos[0] -= u->cammov * ftime;
	else if ((state = glfwGetKey(window, GLFW_KEY_A)) == GLFW_PRESS)
		u->campos[1] += u->cammov * ftime;
	else if ((state = glfwGetKey(window, GLFW_KEY_D)) == GLFW_PRESS)
		u->campos[1] -= u->cammov * ftime;
	else
		return ;
	glUniform3f(u->icampos, u->campos[0], u->campos[1], u->campos[2]);
}

void		poll_keys(GLFWwindow *window, float ftime)
{
	t_uniforms		*u;

	u = get_uniforms();
	poll_movement_keys(window, ftime, u);
}
