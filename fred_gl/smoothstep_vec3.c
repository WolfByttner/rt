/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smoothstep_vec3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/08 15:35:49 by fnieto            #+#    #+#             */
/*   Updated: 2016/01/09 11:42:32 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fred_gl.h"

t_vec3		smoothstep_vec3(t_vec3 e0, t_vec3 e1, t_vec3 x)
{
	x.x = SMOOTHSTEP(e0.x, e1.x, x.x);
	x.y = SMOOTHSTEP(e0.y, e1.y, x.y);
	x.z = SMOOTHSTEP(e0.z, e1.z, x.z);
	return (x);
}

t_vec3		smoothstep_vec3_1(t_float e0, t_float e1, t_vec3 x)
{
	x.x = SMOOTHSTEP(e0, e1, x.x);
	x.y = SMOOTHSTEP(e0, e1, x.y);
	x.z = SMOOTHSTEP(e0, e1, x.z);
	return (x);
}
