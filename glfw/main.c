/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 21:44:02 by fnieto            #+#    #+#             */
/*   Updated: 2016/03/10 21:46:23 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <GLFW/glfw3.h>
#include "rt.h"
#include <stdio.h>

static int		ft_strcmp(const char *a, const char *b)
{
	while (*a && *b)
	{
		if (*a != *b)
			return (*a - *b);
		++a;
		++b;
	}
	return (*a - *b);
}

static t_params	*init_params(int ac, char **av)
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
}

static t_rt		*init_rt(t_params *pms)
{
	static t_rt		rt;

	if (!pms)
		return (&rt);
	rt.pms = pms;
	rt.frame = malloc_smem(pms->res[0] * pms->res[1] * sizeof(int));
	return (&rt);
}

static void		deinit_rt(void)
{
	t_rt	*rt;

	rt = init_rt(0);
	free_smem(&(rt->frame));
}

int				main(int ac, char **av)
{
	GLFWwindow		*window;
	t_rt			*rt;
	int				i;

	rt = init_rt(init_params(ac, av));
	if (!glfwInit())
		err("GLFW failed to init\n");
	glfwWindowHint(GLFW_RESIZABLE, 0);
	window = glfwCreateWindow(rt->pms->res[0], rt->pms->res[1], P_NAME, 0, 0);
	if (!window)
	{
		glfwTerminate();
		err("GLFW failed to create window");
	}
	glfwMakeContextCurrent(window);
	glfwSwapInterval(0);
	GEN_GRID(rt->pms->res[0], rt->pms->res[1]);
	i = -1;
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT);
		CUDA_CALL(test_kernel, grid, 1, (int*)rt->frame->device, ++i);
		sync_host(rt->frame);
		glDrawPixels(rt->pms->res[0], rt->pms->res[1], GL_RGBA,
			GL_UNSIGNED_INT_8_8_8_8, rt->frame->host);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	deinit_rt();
	return (0);
}
