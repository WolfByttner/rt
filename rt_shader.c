/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_shader.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/10 00:00:53 by fnieto            #+#    #+#             */
/*   Updated: 2016/03/07 16:49:15 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define CL_CONTEXT
#include "shader.h"
#include "sphere.c"


CL_FUNC float3 reflect(float3 v, float3 n)
{
	return (v - 2.0f * dot(v, n) * n);
}

CL_FUNC int			encode(float3 col)
{
	int		val;
	float v0 = 0.;
	float v1 = 1.;

	val = 0x10000 * (int)(clamp(col.x, v0, v1) * 255.);
	val = val + 0x100 * (int)(clamp(col.y, v0, v1) * 255.);
	val = val + 0x1 * (int)(clamp(col.z, v0, v1) * 255.);
	return (val);
}

CL_FUNC t_ret		raytrace(t_cam cam, t_geo *geoms, size_t size)
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

CL_FUNC float3		rotate_vec(float3 vec, float3 angls)
{
	float2		xrot;
	float2		yrot;
	float2		zrot;
	float3		tmp;

	tmp = vec;
	zrot.x = cos(angls.z);
	zrot.y = sin(angls.z);
	tmp = ((float3)(tmp.x, tmp.y * zrot.x - tmp.z * zrot.y,
		tmp.y * zrot.y + tmp.z * zrot.x));
		yrot.x = cos(angls.y);
	yrot.y = sin(angls.y);
	tmp = ((float3)(tmp.x * yrot.x + tmp.z * xrot.y, tmp.y,
		-tmp.x * xrot.y + tmp.z * xrot.x));
	xrot.x = cos(angls.x);
	xrot.y = sin(angls.x);
	tmp = ((float3)(tmp.x * xrot.x - tmp.y * xrot.y,
		tmp.x * xrot.y + tmp.y * xrot.x, tmp.z));
	return (tmp);
}

CL_FUNC float3		make_view_vector(float2 angl)
{

	return (normalize((float3)(sin(angl.y) * cos(angl.x), sin(angl.y) *
		sin(angl.x), cos(angl.y))).xzy);
}

CL_FUNC float3		paint(t_cam cam, t_light *lights, t_ret *last, int2 sz)
{
	float3	diffuse;
	float3	specular;
	float3	li;
	int		i;

	diffuse = (float3)(0, 0, 0);
	i = -1;
	while (++i < sz.x)
	{
		li = normalize(lights[i].pos - (last[0].t * cam.ray + cam.pos));
		diffuse += max(dot(last[0].normal, li), (float)(0)) * lights[i].color;
		specular = pow(max(dot(reflect(-li, last[0].normal), -cam.ray),
			(float)(0)), last[0].object.mat.shine_dampener) * lights[i].color *
			last[0].object.mat.reflectivity;
	}
	return (diffuse * last[0].object.mat.color + specular);
}

CL_FUNC t_ret		render(t_cam cam, t_geo *objects, t_light *lights, int2 sz)
{
	t_ret	rets[ITERATIONS];
	t_cam	cams[ITERATIONS];
	int		i;
	int		j;

	cams[0] = cam;
	i = -1;
	while (++i < ITERATIONS)
	{
		rets[i] = raytrace(cams[i], objects, sz.x);
		if (rets[i].t > 0)
			rets[i].normal = sphere_norm(cams[i], rets[i]);
		if (i == ITERATIONS - 1 || rets[i].t < 0)
			break;
		cams[i + 1].pos = rets[i].t * cams[i].ray - (float)(0.001);
		cams[i + 1].ray = reflect(cams[i].ray, rets[i].normal);
	}
	j = i + 1;
	while (--j >= 0)
		rets[j].color = paint(cams[j], lights, &(rets[j]),
			(int2)(sz.y, 1 + (i != j)));
	return (rets[0]);
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
	float2				coord;
	float2				uv;
	t_cam				cam;
	float2				fres = convert_float2(res);
	float2				frot = convert_float2(rot);
	float3				fpos = convert_float3(pos);
	float4				fmouse = convert_float4(mouse);
	float				fzoom = convert_float(zoom);
	float				ftime = convert_float(time);
	t_geo				spheres[] = {
		{0, WHITE_MAT, {0, 0, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
		{0, WHITE_MAT, {0, 0, 10, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
		{0, RED_MAT, {0, 0, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}}
	};
	t_light				lights[] = {
		{{3, 3, -3}, {1, 0.5, 0.5}},
		{{-3, 3, -3}, {0.5, 1, 0.5}},
		{{0, -3, 0}, {0.5, 0.5, 1}}
	};

	id = get_global_id(0);
	if (((size_t)id) >= count)
		return ;
	coord = (float2)((id % (int)(fres.x)), id / ((int)(fres.x)));
	uv = -((coord / fres) - (float)(0.5)) * (float2)(1, -1) * normalize(fres * fzoom) * PI / 2 - frot * PI / 50 + PI / 2;
	cam.ray = make_view_vector(uv);
	cam.pos = fpos.xzy * (float3)(-10, 0.1, 10) + (float3)(0, 0, 0);
	t_ret tmp = render(cam, spheres, lights, (int2)(sizeof(spheres) /
		sizeof(t_geo), sizeof(lights) / sizeof(t_light)));
	int m = mode % 4;

	if (m == 0)
		output[id] = encode(tmp.normal);
	else if (m == 1)
		output[id] = encode((float3)(1 / (tmp.t + (tmp.t != -1))));
	else if (m == 2)
		output[id] = encode(length(tmp.color) > 1 ? normalize(tmp.color) : tmp.color);
	else if (m == 3)
		output[id] = encode(tmp.color);
	if (tmp.t == -1)
		output[id] = 0;
}
