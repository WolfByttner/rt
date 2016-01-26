/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/09 12:02:27 by fnieto            #+#    #+#             */
/*   Updated: 2016/01/18 18:48:19 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fred_gl.h"
#include <math.h>

t_mat4		mat4(t_vec4 r1, t_vec4 r2, t_vec4 r3, t_vec4 r4)
{
	t_mat4	new;

	new.m00 = r1.x;
	new.m10 = r1.y;
	new.m20 = r1.z;
	new.m30 = r1.w;
	new.m01 = r2.x;
	new.m11 = r2.y;
	new.m21 = r2.z;
	new.m31 = r2.w;
	new.m02 = r3.x;
	new.m12 = r3.y;
	new.m22 = r3.z;
	new.m32 = r3.w;
	new.m03 = r4.x;
	new.m13 = r4.y;
	new.m23 = r4.z;
	new.m33 = r4.w;
	return (new);
}

t_mat4		mat4_identity(void)
{
	static const t_mat4	identity = {
		1., 0., 0., 0.,
		0., 1., 0., 0.,
		0., 0., 1., 0.,
		0., 0., 0., 1.};

	return (identity);
}

t_mat4		mat4_scale(t_vec3 scale)
{
	t_mat4	new;

	new = mat4_identity();
	new.m00 = scale.x;
	new.m11 = scale.y;
	new.m22 = scale.z;
	return (new);
}

t_mat4		mat4_translation(t_vec3 translation)
{
	t_mat4	new;

	new = mat4_identity();
	new.m03 = translation.x;
	new.m13 = translation.y;
	new.m23 = translation.z;
	return (new);
}

t_mat4		mat4_rotation(t_vec3 axis, t_float angle)
{
	t_mat4	new;
	t_float	c;
	t_float	s;

	new = mat4_identity();
	c = cos(angle);
	s = sin(angle);
	new.m00 = axis.x * axis.x * (1 - c) + c;
	new.m10 = axis.x * axis.y * (1 - c) - axis.z * s;
	new.m20 = axis.x * axis.z * (1 - c) + axis.y * s;
	new.m01 = axis.x * axis.y * (1 - c) + axis.z * s;
	new.m11 = axis.y * axis.y * (1 - c) + c;
	new.m21 = axis.y * axis.z * (1 - c) + axis.x * s;
	new.m02 = axis.x * axis.z * (1 - c) - axis.y * s;
	new.m12 = axis.y * axis.z * (1 - c) + axis.x * s;
	new.m22 = axis.z * axis.z * (1 - c) + c;
	return (new);
}
