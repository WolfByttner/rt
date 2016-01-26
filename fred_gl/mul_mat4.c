/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mul_mat4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/09 13:33:48 by fnieto            #+#    #+#             */
/*   Updated: 2016/01/09 14:43:59 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fred_gl.h"

t_mat4			mul_mat4(t_mat4 a, t_mat4 b)
{
	t_mat4	new;

	new.m00 = a.m00 * b.m00 + a.m10 * b.m01 + a.m20 * b.m02 + a.m30 * b.m03;
	new.m10 = a.m00 * b.m10 + a.m10 * b.m11 + a.m20 * b.m12 + a.m30 * b.m13;
	new.m20 = a.m00 * b.m20 + a.m10 * b.m21 + a.m20 * b.m22 + a.m30 * b.m23;
	new.m30 = a.m00 * b.m30 + a.m10 * b.m31 + a.m20 * b.m32 + a.m30 * b.m33;
	new.m01 = a.m01 * b.m00 + a.m11 * b.m01 + a.m21 * b.m02 + a.m31 * b.m03;
	new.m11 = a.m01 * b.m10 + a.m11 * b.m11 + a.m21 * b.m12 + a.m31 * b.m13;
	new.m21 = a.m01 * b.m20 + a.m11 * b.m21 + a.m21 * b.m22 + a.m31 * b.m23;
	new.m31 = a.m01 * b.m30 + a.m11 * b.m31 + a.m21 * b.m32 + a.m31 * b.m33;
	new.m02 = a.m02 * b.m00 + a.m12 * b.m01 + a.m22 * b.m02 + a.m32 * b.m03;
	new.m12 = a.m02 * b.m10 + a.m12 * b.m11 + a.m22 * b.m12 + a.m32 * b.m13;
	new.m22 = a.m02 * b.m20 + a.m12 * b.m21 + a.m22 * b.m22 + a.m32 * b.m23;
	new.m32 = a.m02 * b.m30 + a.m12 * b.m31 + a.m22 * b.m32 + a.m32 * b.m33;
	new.m03 = a.m03 * b.m00 + a.m13 * b.m01 + a.m23 * b.m02 + a.m33 * b.m03;
	new.m13 = a.m03 * b.m10 + a.m13 * b.m11 + a.m23 * b.m12 + a.m33 * b.m13;
	new.m23 = a.m03 * b.m20 + a.m13 * b.m21 + a.m23 * b.m22 + a.m33 * b.m23;
	new.m33 = a.m03 * b.m30 + a.m13 * b.m31 + a.m23 * b.m32 + a.m33 * b.m33;
	return (new);
}

t_mat4			mul_mat4_1(t_mat4 a, t_float b)
{
	a.m00 *= b;
	a.m10 *= b;
	a.m20 *= b;
	a.m30 *= b;
	a.m01 *= b;
	a.m11 *= b;
	a.m21 *= b;
	a.m31 *= b;
	a.m02 *= b;
	a.m12 *= b;
	a.m22 *= b;
	a.m32 *= b;
	a.m03 *= b;
	a.m13 *= b;
	a.m23 *= b;
	a.m33 *= b;
	return (a);
}

t_vec4			mul_mat4_vec4(t_mat4 a, t_vec4 b)
{
	t_vec4	new;

	new.x = a.m00 * b.x + a.m10 * b.y + a.m20 * b.z + a.m30 * b.w;
	new.y = a.m01 * b.x + a.m11 * b.y + a.m21 * b.z + a.m31 * b.w;
	new.z = a.m02 * b.x + a.m12 * b.y + a.m22 * b.z + a.m32 * b.w;
	new.w = a.m03 * b.x + a.m13 * b.y + a.m23 * b.z + a.m33 * b.w;
	return (new);
}

t_vec3			mul_mat4_vec3(t_mat4 a, t_vec3 b)
{
	t_vec3	new;

	new.x = a.m00 * b.x + a.m10 * b.y + a.m20 * b.z + a.m30;
	new.y = a.m01 * b.x + a.m11 * b.y + a.m21 * b.z + a.m31;
	new.z = a.m02 * b.x + a.m12 * b.y + a.m22 * b.z + a.m32;
	return (new);
}
