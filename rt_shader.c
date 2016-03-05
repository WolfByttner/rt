/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_shader.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/10 00:00:53 by fnieto            #+#    #+#             */
/*   Updated: 2016/03/05 20:57:58 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define CL_CONTEXT
#include "shader.h"
#pragma OPENCL EXTENSION cl_khr_fp64 : enable


static inline int			encode(double3 col)
{
	int		val;

	val = 0x10000 * (int)(clamp(col.x, 0., 1.) * 255.);
	val = val + 0x100 * (int)(clamp(col.y, 0., 1.) * 255.);
	val = val + 0x1 * (int)(clamp(col.z, 0., 1.) * 255.);
	return (val);
}

static inline t_ret		sphere_dst(t_cam cam, t_geo sp, t_ret prev)
{
	t_ret		ret;
	double3		rc;
	double3		v;

	rc = cam.pos-sp.pos;
	double c = dot(rc, rc) - (sp.dim.x*sp.dim.x);
	double b = dot(cam.ray, rc);
	double d = b*b - c;
	double t = -b - sqrt(fabs(d));
	double st = step(0.0, min(t,d));
	double m = mix(-1.0, t, st);
	ret.t = m;
	if ((ret.t > 0 && prev.t <= 0) || (ret.t > 0 && prev.t > 0 && ret.t < prev.t))
	{
		ret.object = sp;
		return (ret);
	}
	ret = prev;
	return (ret);
}

static inline double3		sphere_norm(t_cam cam, t_ret ret)
{
	return (-normalize(ret.object.pos - (cam.pos+cam.ray*ret.t)));
}

static inline t_ret		raytrace(t_cam cam, t_geo *geoms, size_t size)
{
	size_t		i;
	t_ret		tmp;

	tmp.t = -1;
	i = -1;
	while (++i < size)
		if (geoms[i].type == 0)
			tmp = sphere_dst(cam, geoms[i], tmp);
	return (tmp);
}

static inline double3		rotate_vec(double3 vec, double3 angls)
{
	double2		xrot;
	double2		yrot;
	double2		zrot;
	double3		tmp;

	tmp = vec;
	zrot.x = cos(angls.z);
	zrot.y = sin(angls.z);
	tmp = ((double3)(tmp.x, tmp.y * zrot.x - tmp.z * zrot.y,
		tmp.y * zrot.y + tmp.z * zrot.x));
		yrot.x = cos(angls.y);
	yrot.y = sin(angls.y);
	tmp = ((double3)(tmp.x * yrot.x + tmp.z * xrot.y, tmp.y,
		-tmp.x * xrot.y + tmp.z * xrot.x));
	xrot.x = cos(angls.x);
	xrot.y = sin(angls.x);
	tmp = ((double3)(tmp.x * xrot.x - tmp.y * xrot.y,
		tmp.x * xrot.y + tmp.y * xrot.x, tmp.z));
	return (tmp);
}

static inline double3		make_view_vector(double2 angl)
{

	return (normalize((double3)(sin(angl.y) * cos(angl.x), sin(angl.y) *
		sin(angl.x), cos(angl.y))).xzy);
}

__kernel void		shader(
		__global const int* input,
		__global int* output,
		const size_t count,		//max des ids (ne pas toucher)
		const double2 res,		//resolution de l'ecran
		const double2 rot,		//rotation (fleches)
		const double3 pos,		//position (x: ad; y: ws, z: qe)
		const double4 mouse,	//position souris: xy, dernier click: zw
		const double zoom,		//zoom +- (pas pave numerique)
		const double time,		//temps
		const size_t frame,		//frame (nombe d'iterations passe, utile pour montecarlo)
		const size_t mode)		//incrementer avec barre d'espace: il faut le modulo.
{
	int		id;
	double2				coord;
	double2				uv;
	t_cam				cam;
	t_geo				spheres[] = {{0, {0, 0, 2}, {1, 0, 0}, {0, 0, 0}},
		{0, {0, 0, 10}, {5, 0, 0}, {0, 0, 0}},
		{0, {0, 0, 3}, {1, 0, 0}, {0, 0, 0}}};

	id = get_global_id(0);
	if (((size_t)id) >= count)
		return ;
	coord = (double2)((id % (int)(res.x)), id / ((int)(res.x)));
	uv = -((coord / res) - 0.5) * (double2)(1, -1) * normalize(res) * zoom
		* PI / 2 - rot * PI / 50 + PI / 2;
	cam.ray = make_view_vector(uv);
	cam.pos = pos.xzy * (double3)(-10, 0.1, 10) + (double3)(0, 0, 0);
	t_ret tmp;
	tmp = raytrace(cam, spheres, sizeof(spheres) / sizeof(t_geo));
	if (tmp.t > 0)
		tmp.normal = sphere_norm(cam, tmp);
//	output[id] = *(long*)&t;
	output[id] = encode((double3)(tmp.normal));
}

