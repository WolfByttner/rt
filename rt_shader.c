/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_shader.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/10 00:00:53 by fnieto            #+#    #+#             */
/*   Updated: 2016/03/08 20:24:00 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define CL_CONTEXT
#include "shader.h"
#include "sphere.c"
#include "plane.c"


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
	{
		if (geoms[i].type == SPHERE)
			tmp = sphere_dst(cam, geoms[i], tmp);
		else if (geoms[i].type == PLANE)
			tmp = plane_dst(cam, geoms[i], tmp);
	}
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

CL_FUNC float3		paint(t_cam cam, t_light *lights, t_ret *last, t_geo *objs, int3 sz)
{
	float3	diffuse;
	float3	specular;
	float3	li;
	t_cam	newcam;
	int		i;

	diffuse = (float3)(0, 0, 0);
	specular = (float3)(0, 0, 0);
	i = -1;
	while (++i < sz.x)
	{
		newcam.pos = (last[0].t - (float)(0.001)) * cam.ray + cam.pos;
		li = lights[i].pos - (newcam.pos);
		newcam.ray = normalize(li);
		li.z = li.x * li.x + li.y * li.y + li.z * li.z;
		li.y = raytrace(newcam, objs, sz.z).t;
		li.x = half_sqrt(li.z);
		if (li.y < li.x && li.y != -1)
			continue;
		li.z = min((float)(1), 1/li.x * 100);
		diffuse += max(dot(last[0].normal, newcam.ray), (float)(0)) *
			lights[i].color * li.z;
		specular += pow(max(dot(reflect(-newcam.ray, last[0].normal), -cam.ray),
			(float)(0)), last[0].object.mat.shine_dampener) *
			last[0].object.mat.reflectivity * lights[i].color * li.z;
	}
	if (sz.y > 1 && last[1].t > 0)
		specular += last[1].color * last[0].object.mat.reflectivity;
	return (diffuse * last[0].object.mat.color + specular);
}

CL_FUNC t_ret		render(t_cam cam, t_geo *objects, t_light *lights, int2 sz)
{
	t_ret	rets[ITERATIONS];
	t_cam	cams[ITERATIONS];
	t_cam	new;
	int		i;
	int		j;

	cams[0] = cam;
	i = -1;
	while (++i < ITERATIONS)
	{
		rets[i] = raytrace(cams[i], objects, sz.x);
		if (i == ITERATIONS - 1 || rets[i].t < 0)
			break;
		new.pos = (rets[i].t - (float)(0.001)) * cams[i].ray + cams[i].pos;
		new.ray = reflect(cams[i].ray, rets[i].normal);
		cams[i + 1] = new;
	}
	j = i + 1;
	while (--j >= 0)
		rets[j].color = paint(cams[j], lights, &(rets[j]), objects,
			(int3)(sz.y, 1 + (i != j), sz.x));
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
	float3				fpos = convert_float3(pos) * 4;
	float4				fmouse = convert_float4(mouse);
	float				fzoom = convert_float(zoom);
	float				ftime = convert_float(time);
	t_geo				spheres[] = {
		{SPHERE, WHITE_MAT, {0, 0, 22, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
		//{SPHERE, WHITE_GLOSSY, {0, 0, 30, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
		//{SPHERE, BLUE_MAT, {0, 2, 23, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
		{PLANE, RED_MAT, {0, -5, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
		//{PLANE, WHITE_MAT, {0, 5, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
		//{PLANE, MIRROR, {-5, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
		{PLANE, MIRROR, {5, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}}
	};
	t_light				lights[] = {
		{{3, 3, 17}, {1, 0.5, 0.5}},
		{{-3, 3, 17}, {0.5, 1, 0.5}},
		{{0, -3,20}, {1, 1, 1}}
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
	int m = (mode - 1) % 4;

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
