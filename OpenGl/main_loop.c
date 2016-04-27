/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbyttner <jbyttner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/27 20:09:53 by jbyttner          #+#    #+#             */
/*   Updated: 2016/04/27 20:27:55 by jbyttner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <sys/time.h>

static inline long	get_program_time(void)
{
	struct timeval	tval;

	gettimeofday(&tval, 0);
	return (tval.tv_sec * 1e6 + tval.tv_usec);
}

static inline void	init_main_loop(long t[2], long *start_t, long *told,
						int *fps)
{
	t[0] = get_program_time();
	*start_t = t[0];
	t[1] = t[0];
	*told = t[0];
	*fps = 0;
}

void				main_loop(GLFWwindow *window,
		GLint ires, GLint itime, t_properties *properties)
{
	long	t[2];
	long	start_t;
	long	told;
	int		fps;

	init_main_loop(t, &start_t, &told, &fps);
	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glUniform2i(ires, properties->width, properties->height);
		glUniform1f(itime, (float)((double)(t[1] - start_t) / 1000000.0f));
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);
		glfwPollEvents();
		++fps;
		if ((t[1] = get_program_time()) > t[0] + 1000000)
		{
			ft_putnbr(fps);
			ft_putendl(" fps");
			t[0] = t[1];
			fps = 0;
		}
		poll_keys(window, (float)(t[1] - told) / 1000000.0f);
		told = t[1];
	}
}
