/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   poll_keys.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbyttner <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/29 20:50:54 by jbyttner          #+#    #+#             */
/*   Updated: 2016/04/04 22:53:54 by jbyttner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_input.h"
#include <math.h>
#include <stdio.h>

/*
** Rotation by hardcoded 3x3 rotation matrix
*/

/* -- rot z --
** 1, 			0,  	    0
** 0, 			w, 			-z
** 0, 			z, 			w
** -- rot y --
** y,  		0, 			x 
** 0,    		1, 			0, 
** x  		0, 			y
** -- rot res --
** y			0			x
** x * z		w			-z * y
** -w * x		z			y * w
*/

static void	translate_key_move(t_uniforms *u, float move[3])
{
	float	*a;
	float	sins[4];

	a = u->camrot;
	sins[0] = sin(a[0]);
	sins[1] = cos(a[0]);
	sins[2] = sin(a[1]);
	sins[3] = cos(a[1]);
	u->campos[0] += sins[1] * move[0] + sins[0] * move[2];
	u->campos[1] += sins[2] * sins[0] * move[0]
		+ sins[3] * move[1]
		- sins[2] * sins[1] * move[2];
	u->campos[2] += -sins[3] * sins[0] * move[0]
		+ sins[2] * move[1]
		+ sins[1] * sins[3] * move[2];
	printf("move: |%f|%f|%f| degree: |%f|%f| res: |%f|%f|%f|\n", move[0], move[1], move[2],
			a[0], a[1], u->campos[0], u->campos[1], u->campos[2]);
}

static void	poll_movement_keys(GLFWwindow *window, float ftime, t_uniforms *u)
{
	int		state;
	float	move[3];

	memset(move, 0, sizeof move);
	if ((state = glfwGetKey(window, GLFW_KEY_W)) == GLFW_PRESS)
		move[2] = u->cammov * ftime;
	if ((state = glfwGetKey(window, GLFW_KEY_S)) == GLFW_PRESS)
		move[2] = -u->cammov * ftime;
	if ((state = glfwGetKey(window, GLFW_KEY_A)) == GLFW_PRESS)
		move[0] = -u->cammov * ftime;
	if ((state = glfwGetKey(window, GLFW_KEY_D)) == GLFW_PRESS)
		move[0] = u->cammov * ftime;
	if ((state = glfwGetKey(window, GLFW_KEY_SPACE)) == GLFW_PRESS)
		move[1] = u->cammov * ftime;
	if ((state = glfwGetKey(window, GLFW_KEY_LEFT_SHIFT)) == GLFW_PRESS)
		move[1] = -u->cammov * ftime;
	if ((state = glfwGetKey(window, GLFW_KEY_ESCAPE)) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, 1);
	translate_key_move(u, move);
	glUniform3f(u->icampos, u->campos[0], u->campos[1], u->campos[2]);
}

void		poll_keys(GLFWwindow *window, float ftime)
{
	t_uniforms		*u;

	u = get_uniforms();
	poll_movement_keys(window, ftime, u);
}
