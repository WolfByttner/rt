/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader_torus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/02 22:44:31 by fnieto            #+#    #+#             */
/*   Updated: 2016/05/04 05:51:51 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

float		torus_res_2(float d1, float d2, float p3, float z)
{
	float	result;
	float	t1;
	float	t2;
	float	h;

	result = 1e20;
	if ((h = sqrt(d1 * d1 - z + d2)) > 0.0)
	{
		t1 = -d1 - h - p3;
		t2 = -d1 + h - p3;
		if (t1 > 0.0)
			result = t1;
		else if (t2 > 0.0)
			result = t2;
	}
	if ((h = sqrt(d1 * d1 - z - d2)) > 0.0)
	{
		t1 = d1 - h - p3;
		t2 = d1 + h - p3;
		if (t1 > 0.0)
			result = min(result, t1);
		else if (t2 > 0.0)
			result = min(result, t2);
	}
	return (result);
}

float		torus_res_1(vec4 p3)
{
	vec3	p1;
	vec4	p2;
	vec3	p4;

	p1.x = (-3 * pow(p3.x, 2) + 2 * p3.y) / 3;
	p1.y = 2 * pow(p3.x, 3) - 2 * p3.x * p3.y + 2.0 * p3.z;
	p1.z = (-3 * pow(p3.x, 4) + 4 * p3.x * p3.x * p3.y - 8 * p3.x * p3.z + 4
		* p3.w) / 3;
	p2.x = p1.x * p1.x + p1.z;
	p2.y = 3 * p1.z * p1.x - p1.x * p1.x * p1.x - p1.y * p1.y;
	p2.z = p2.y * p2.y - pow(p2.x, 3);
	p4.z = 0;
	p2.w = (p2.z < 0) ? sqrt(p2.x) : pow(sqrt(p2.z) + abs(p2.y), 1. / 3);
	p4.z = (p2.z < 0) ? 2 * p2.w * cos(acos(p2.y / (p2.w * p2.x)) / 3) :
		sign(p2.y) * abs(p2.w + p2.x / p2.w);
	p4.z = p1.x - p4.z;
	p4.x = p4.z - 3.0 * p1.x;
	p4.y = p4.z * p4.z - 3.0 * p1.z;
	if ((abs(p4.x) < 1.0e-4) ? p4.y < 0 : p4.x < 0)
		return (-1.0);
	p4.x = (abs(p4.x) < 1.0e-4) ? p4.x : sqrt(p4.x / 2.0);
	p4.y = (abs(p4.x) < 1.0e-4) ? sqrt(p4.y) : p1.y / p4.x;
	return (torus_res_2(p4.x, p4.y, p3.x, p4.z));
}

/*
** sp.a.x is radius;
** sp.a.y is thickness;
*/

float		torus(s_cam cam, s_geo sp)
{
	vec3	pos;
	vec4	p1;
	vec4	p2;
	vec4	p3;
	float	odst;

	pos = cam.pos - sp.pos;
	p2.y = length(pos);
	if (p2.y > 2 * (sp.a.x + sp.a.y))
		pos += cam.ray * (p2.y - 2 * (sp.a.x + sp.a.y));
	p1.x = sp.a.x * sp.a.x;
	p1.y = sp.a.y * sp.a.y;
	p1.z = dot(pos, pos);
	p1.w = dot(pos, cam.ray);
	if (p1.w > 0 && p1.z > pow(sp.a.x + sp.a.y, 2))
		return (-1);
	p2.x = (p1.z - p1.y - p1.x) * .5;
	p3.x = p1.w;
	p3.y = p1.w * p1.w + p1.x * cam.ray.z * cam.ray.z + p2.x;
	p3.z = p2.x * p1.w + p1.x * pos.z * cam.ray.z;
	p3.w = p2.x * p2.x + p1.x * pos.z * pos.z - p1.x * p1.y;
	p2.z = torus_res_1(p3);
	return (mix(-1, p2.z + ((p2.y > 2 * (sp.a.x + sp.a.y)) ?
		(p2.y - 2 * (sp.a.x + sp.a.y)) : 0), step(0, p2.z)));
}

vec3		ntorus(vec3 pos, vec2 tor)
{
	return (normalize(pos * (dot(pos, pos) - tor.y * tor.y -
					tor.x * tor.x * VEC3(1.0, 1.0, -1.0))));
}

s_res		torus_dst(s_geo sp, s_cam cam, s_res prev)
{
	s_res ret;

	ret.dst = torus(cam, sp);
	if (ret.dst > 0 && (ret.dst < prev.dst || prev.dst < 0))
	{
		ret.mat = sp.mat;
		ret.cam = cam;
		ret.normal = ntorus(cam.pos - sp.pos + ret.dst * cam.ray, sp.a.xy);
		return (ret);
	}
	return (prev);
}
