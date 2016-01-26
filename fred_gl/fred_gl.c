/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fred_gl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/08 19:45:30 by fnieto            #+#    #+#             */
/*   Updated: 2016/01/18 17:59:28 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fred_gl.h"
#include "libft.h"

static t_instance	*inst_cont(t_instance *inst, int mode)
{
	static t_instance	*instance = 0;

	if (mode == GL_SET)
		instance = inst;
	return (instance);
}

void				fred_gl_init(size_t w, size_t h, t_draw_func drawfn)
{
	t_instance *i;

	i = inst_cont(0, GL_GET);
	if (!i)
	{
		i = inst_cont((t_instance*)ft_memalloc(sizeof(t_instance)), GL_SET);
		if (!i)
			return ;
		i->w = w;
		i->h = h;
		i->drawfn = drawfn;
		i->frame = frame(w, h);
	}
}

void				fred_gl_deinit(void)
{
	t_instance	*i;

	i = inst_cont(0, GL_GET);
	frame_del(&(i->frame));
	ft_memdel((void**)&i);
	inst_cont(0, GL_SET);
}

t_instance			*get_instance(void)
{
	return (inst_cont(0, GL_GET));
}
