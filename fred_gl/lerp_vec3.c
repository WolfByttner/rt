/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lerp_vec3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/08 15:35:49 by fnieto            #+#    #+#             */
/*   Updated: 2016/01/09 11:33:22 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fred_gl.h"

t_vec3		lerp_vec3(t_vec3 a, t_vec3 b, t_vec3 x, t_vec3 max)
{
	a.x = LERP(a.x, b.x, x.x, max.x);
	a.y = LERP(a.y, b.y, x.y, max.y);
	a.z = LERP(a.z, b.z, x.z, max.z);
	return (a);
}

t_vec3		lerp_vec3_1(t_vec3 a, t_vec3 b, t_float x, t_float max)
{
	a.x = LERP(a.x, b.x, x, max);
	a.y = LERP(a.y, b.y, x, max);
	a.z = LERP(a.z, b.z, x, max);
	return (a);
}
