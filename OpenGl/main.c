/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbyttner <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/21 19:38:41 by jbyttner          #+#    #+#             */
/*   Updated: 2016/04/27 21:53:37 by jbyttner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "rt_input.h"

int					main(void)
{
	GLFWwindow			*window;
	t_properties		*properties;

	properties = get_properties();
	window = setup_program(properties);
	properties->ires = glGetUniformLocation(properties->program, "iResolution");
	properties->itime = glGetUniformLocation(properties->program,
			"iGlobalTime");
	glfwSetCursorPosCallback(window, cursor_position_callback);
	main_loop(window, properties);
	ft_putnbr(glGetError());
	ft_putendl(" 2");
	glDeleteShader(properties->shaders[0]);
	glDeleteShader(properties->shaders[1]);
	glDeleteProgram(properties->program);
	glDeleteVertexArrays(1, &(properties->model));
	glDeleteBuffers(1, &(properties->verts));
	glDeleteBuffers(1, &(properties->indices));
	glfwTerminate();
	return (0);
}
