/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/09 16:04:36 by fnieto            #+#    #+#             */
/*   Updated: 2016/01/18 18:36:06 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fred_gl.h"
#include "libft.h"

t_frame		*frame(size_t w, size_t h)
{
	t_frame		*new;
	t_buffer	*bufs[3];
	int			i;

	new = (t_frame*)ft_memalloc(sizeof(t_frame));
	if (!new)
		return (0);
	bufs[0] = buffer(w, h, sizeof(int));
	bufs[1] = buffer(w, h, sizeof(t_float));
	bufs[2] = buffer(w, h, sizeof(char));
	if (!bufs[0] || !bufs[1] || !bufs[2])
	{
		i = -1;
		while (++i < 3)
			if (bufs[i])
				ft_memdel((void**)&(bufs[i]));
		ft_memdel((void**)&new);
		return (0);
	}
	new->img = bufs[0];
	new->depth = bufs[1];
	new->change = bufs[2];
	new->w = w;
	new->h = h;
	return (new);
}

void		frame_put_pixel(t_frame *f, t_vertex v, t_shader shader)
{
	t_shader_info	i;

	if (OUT(v.pos.x, 0, f->w) || OUT(v.pos.y, 0, f->w) || OUT(v.pos.z, -1, 1))
		return ;
	if (f->depth_func && v.pos.z >
		buf_read(f->depth, ROUND(v.pos.x), ROUND(v.pos.y)).tf)
		return ;
	i.i_frag_coord = vec2(ROUND(v.pos.x), ROUND(v.pos.y));
	i.i_resolution = vec2(f->w, f->h);
	i.i_global_time = get_time();
	buf_write(f->img, i.i_frag_coord.x, i.i_frag_coord.y, T(shader(i)));
	if (f->clear_undrawn)
		buf_write(f->change, i.i_frag_coord.x, i.i_frag_coord.y, T(1));
	if (f->depth_func)
		buf_write(f->depth, i.i_frag_coord.x, i.i_frag_coord.y, T(v.pos.z));
}

void		frame_print(t_frame *f)
{
	size_t	x;
	size_t	y;
	char	drawn;
	int		color;
	
	y = -1;
	while (++y < f->h)
	{
		x = -1;
		while (++x < f->w)
		{
			color = buf_read(f->img, x, y).i;
			drawn = buf_read(f->change, x, y).c;
			if (drawn || !f->clear_undrawn)
				get_instance()->drawfn(x, y, color);
			else if (f->clear_undrawn && color)
			{
				get_instance()->drawfn(x, y, 0);
				buf_write(f->img, x, y, T(0));
			}
			if (f->clear_undrawn)
				buf_write(f->change, x, y, T(0));
			if (f->depth_func)
				buf_write(f->depth, x, y, T((t_float)10.));
		}
	}
}

void		frame_del(t_frame **frame)
{
	t_frame	*todel;

	todel = *frame;
	buffer_del(&(todel->img));
	buffer_del(&(todel->depth));
	buffer_del(&(todel->change));
	ft_memdel((void**)frame);
}
