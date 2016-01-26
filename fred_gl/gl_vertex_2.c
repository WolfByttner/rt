/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gl_vertex_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/18 19:55:22 by fnieto            #+#    #+#             */
/*   Updated: 2016/01/18 19:58:22 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fred_gl.h"

void	gl_draw_buf(t_list *buf, t_shader s, t_frame *f, int mode)
{
	static const t_vert_draw	funcs[] = FUNCS;

	funcs[mode](buf, s, f);
}
