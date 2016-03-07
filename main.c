/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/26 18:42:53 by fnieto            #+#    #+#             */
/*   Updated: 2016/03/07 18:51:55 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "mlx.h"

t_mlx		g_mlx;
t_params	g_pms;

int			draw_frame(int x, int y, int color)
{
	return (x & y & color);
}

int			loop_hook(void *params)
{
	t_cl_shader_info	*info;
	/*static t_attrib			def[8];
	  t_vertex				a;
	  t_vertex				b;
	  size_t					i;

	  i = -1;
	  while (++i < 8)
	  {
	  def[i] = attrib_null();
	  }
	  i = -1;
	  while (++i < g_pms.res.y)
	  {
	  a = vertex(vec3(0, (t_float)i, 0), def);
	  b = vertex(vec3(g_pms.res.x, (t_float)i, 0), def);
	  draw_line(a, b, &shader, get_instance()->frame);
	  }*/
	info = get_shader_info();
	set_time(get_time() + 0.1);
	info->time = (double)clock() / CLOCKS_PER_SEC;
	info->frame++;
	run_shader(get_instance()->frame->img);
	mlx_put_image_to_window(g_mlx.core, g_mlx.window, g_mlx.frame, 0, 0);
	return ((int)params);
}

int			key_hook(int keycode, void *params)
{
	t_cl_shader_info	*info;

	info = get_shader_info();
	if (keycode == 53)
	{
		deinit_cl();
		exit(0);
	}
	if (keycode == 24 || keycode == 27)
		info->zoom *= (keycode == 24 ? 1.1 : .9);
	if (keycode == 12 || keycode == 14)
		info->pos.z += (keycode - 13);
	if (keycode == 1 || keycode == 13)
		info->pos.y += (keycode == 1 ? -1 : 1) * (1. / info->zoom) * 0.01;
	if (keycode == 0 || keycode == 2)
		info->pos.x -= (1. / info->zoom) * 0.01 * (keycode - 1);
	if (keycode == 126 || keycode == 125)
		info->rot.y += (keycode == 126 ? 1 : -1);
	if (keycode == 123 || keycode == 124)
		info->rot.x += (keycode == 123 ? -1 : 1);
	if (keycode == 49)
		info->mode++;
	printf("%zu; %e\n",(size_t)info->pos.z, info->zoom);
	ft_putchar('\n');
	return ((int)params);
}

int			cursor_hook(int x, int y, void *params)
{
	t_cl_shader_info	*info;

	info = get_shader_info();
	info->mouse.x = CLAMP(x, 0, info->res.x);
	info->mouse.y = CLAMP(y, 0, info->res.y);
	return ((int)(params = 0));
}

int			mouse_hook(int button, int x,int y, void *params)
{
	t_cl_shader_info	*info;

	info = get_shader_info();
	info->mouse.z = CLAMP(x, 0, info->res.x);
	info->mouse.w = CLAMP(y, 0, info->res.y);
	return ((int)(params = 0) & button & x & y);
}

int			main(int ac, char **av)
{
	int					i;
	t_cl_shader_info	*info;

	g_mlx.core = mlx_init();
	info = get_shader_info();
	g_pms.ac = ac;
	g_pms.av = av;
	g_pms.res = vec2(1024, 1024);
	ft_bzero(info, sizeof(t_cl_shader_info));
	info->res.x = g_pms.res.x;
	info->res.y = g_pms.res.y;
	info->zoom = 1;
	fred_gl_init(g_pms.res.x, g_pms.res.y, &draw_frame);
	ft_putnbr(init_cl(RT_DEVICE_TYPE, "#include <rt_shader.c>",
		g_pms.res.x * g_pms.res.y));
	ft_putchar('\n');
	g_mlx.window = mlx_new_window(g_mlx.core, g_pms.res.x, g_pms.res.y, "rt");
	g_mlx.frame = mlx_new_image(g_mlx.core, g_pms.res.x, g_pms.res.y);
	free(get_instance()->frame->img->buf);
	get_instance()->frame->img->buf = mlx_get_data_addr(g_mlx.frame, &i, &i,
		&i);
	mlx_loop_hook(g_mlx.core, &loop_hook, 0);
	mlx_mouse_hook(g_mlx.window, &mouse_hook, 0);
	mlx_hook(g_mlx.window, 2, 4, &key_hook, 0);
	mlx_hook(g_mlx.window, 6, 1<<6, &cursor_hook, 0);
	ft_putnbr(run_shader(get_instance()->frame->img));
	mlx_loop(g_mlx.core);
}
