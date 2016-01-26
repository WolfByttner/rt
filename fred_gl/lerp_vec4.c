/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lerp_vec4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/08 15:35:49 by fnieto            #+#    #+#             */
/*   Updated: 2016/01/09 11:34:42 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fred_gl.h"

t_vec4		lerp_vec4(t_vec4 a, t_vec4 b, t_vec4 x, t_vec4 max)
{
	a.x = LERP(a.x, b.x, x.x, max.x);
	a.y = LERP(a.y, b.y, x.y, max.y);
	a.z = LERP(a.z, b.z, x.z, max.z);
	a.w = LERP(a.w, b.w, x.w, max.w);
	return (a);
}

t_vec4		lerp_vec4_1(t_vec4 a, t_vec4 b, t_float x, t_float max)
{
	a.x = LERP(a.x, b.x, x, max);
	a.y = LERP(a.y, b.y, x, max);
	a.z = LERP(a.z, b.z, x, max);
	a.w = LERP(a.w, b.w, x, max);
	return (a);
}
