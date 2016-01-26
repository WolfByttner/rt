/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smoothstep_vec4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/08 15:35:49 by fnieto            #+#    #+#             */
/*   Updated: 2016/01/09 11:43:42 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fred_gl.h"

t_vec4		smoothstep_vec4(t_vec4 e0, t_vec4 e1, t_vec4 x)
{
	x.x = SMOOTHSTEP(e0.x, e1.x, x.x);
	x.y = SMOOTHSTEP(e0.y, e1.y, x.y);
	x.z = SMOOTHSTEP(e0.z, e1.z, x.z);
	x.w = SMOOTHSTEP(e0.w, e1.w, x.w);
	return (x);
}

t_vec4		smoothstep_vec4_1(t_float e0, t_float e1, t_vec4 x)
{
	x.x = SMOOTHSTEP(e0, e1, x.x);
	x.y = SMOOTHSTEP(e0, e1, x.y);
	x.z = SMOOTHSTEP(e0, e1, x.z);
	x.w = SMOOTHSTEP(e0, e1, x.w);
	return (x);
}
