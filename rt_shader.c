/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_shader.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/10 00:00:53 by fnieto            #+#    #+#             */
/*   Updated: 2016/02/10 00:28:33 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma OPENCL EXTENSION cl_khr_fp64 : enable

static int			encode(double r, double g, double b)
{
	int	val = 0x10000 * (int)(clamp(r, 0., 1.) * 255.);
	val = val + 0x100 * (int)(clamp(g, 0., 1.) * 255.);
	val = val + 0x1 * (int)(clamp(b, 0., 1.) * 255.);
	return (val);
}

__kernel void		shader(
		__global const int* input,
		__global int* output,
		const size_t count,
		const double2 res,
		const double2 rot,
		const double3 pos,
		const double4 mouse,
		const double zoom,
		const double time,
		const size_t frame,
		const size_t mode)
{
	int					id;
	double2				coord;
	double2				uv;

	id = get_global_id(0);
	if (((size_t)id) >= count)
		return ;
	coord = (double2)((id % (int)(res.x)), id / ((int)(res.x)));
	uv = coord / res;
	output[id] = encode(uv.x, uv.y, (sin((double)(time * 3.14)) + 1) / 2);
}

