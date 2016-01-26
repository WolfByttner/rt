/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/26 18:42:53 by fnieto            #+#    #+#             */
/*   Updated: 2016/01/26 19:37:49 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "mlx.h"
#include <stdlib.h>

t_mlx		g_mlx;
t_params	g_pms;

int			draw_frame(int x, int y, int color)
{
	return (x & y & color);
}

int			loop_hook(void *params)
{
	mlx_put_image_to_window(g_mlx.core, g_mlx.window, g_mlx.frame, 0, 0);
	return ((int)params);
}

int			key_hook(int keycode, void *params)
{
	if (keycode == 53)
		exit(0);
	return ((int)params);
}

int			mouse_hook(int button, int x,int y, void *params)
{
	return ((int)params & button & x & y);
}

int			main(int ac, char **av)
{
	int		i;

	g_mlx.core = mlx_init();
	/*
	**mise en place des parametres
	*/
	g_pms.ac = ac;
	g_pms.av = av;
	g_pms.res = vec2(400, 400);
	/*
	**initialisation de fred_gl:
	**la fonction draw frame est celle pour put un pixel au cas ou
	**on ne pourrais pas avoir un buffer direct, ici on en a un
	*/
	fred_gl_init(g_pms.res.x, g_pms.res.y, &draw_frame);
	g_mlx.window = mlx_new_window(g_mlx.core, g_pms.res.x, g_pms.res.y, "RT");
	g_mlx.frame = mlx_new_image(g_mlx.core, g_pms.res.x, g_pms.res.y);
	/*
	**on vient d'initialiser l'image qui sera affichee a chaque frame.
	**on remplace notre frame buffer avec elle
	*/
	free(get_instance()->frame->img->buf);
	get_instance()->frame->img->buf = mlx_get_data_addr(g_mlx.frame, &i, &i, &i);
	mlx_loop_hook(g_mlx.core, &loop_hook, 0);
	mlx_key_hook(g_mlx.window, &key_hook, 0);
	mlx_mouse_hook(g_mlx.window, &key_hook, 0);
	mlx_loop(g_mlx.core);
}
