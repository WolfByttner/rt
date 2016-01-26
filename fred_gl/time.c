/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/18 15:15:48 by fnieto            #+#    #+#             */
/*   Updated: 2016/01/18 18:01:38 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fred_gl.h"

static t_float		time_cont(t_float time, int mode)
{
	static t_float	gtime = 0;

	if (mode == GL_SET)
		gtime = time;
	return (gtime);
}

t_float				get_time(void)
{
	return (time_cont(0, GL_GET));
}

void				set_time(t_float time)
{
	time_cont(time, GL_SET);
}
