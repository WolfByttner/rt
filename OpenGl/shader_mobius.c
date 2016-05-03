/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader_mobius.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/24 13:42:58 by fnieto            #+#    #+#             */
/*   Updated: 2016/05/03 18:13:30 by jpiniau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** I tried deriving this as a cubic from
** y(x**2 + y**2 + z**2 - 1) - 2z(x**2 + y**2 + x) = 0
** from https://calculus7.org/2015/04/27/implicit-mobius-strip/
** --
** for a, b, c, d as the constants in a cubic
** --
** d is short for d.xyz. Operations are by component
** d.xy
** --
** a = (d**2 * d.y - 2 * d.xy**2 * d.z)
** b = (d**2 * p.y + 2 * (d.y * p * d - p.z * d.xy ** 2 - d.x * d.z - 2 * p.xy
** * d.xy))
** c = (d.y * p ** 2 + 2 * p * d * p.y - 2 * p.z * (d.x * 2 * p.xy * d.xy)
** - p.y - 2 * d.z * (p.xy ** 2 + p.x))
** d = (p.y * p ** 2 - 2 * p.z * (p.xy ** 2 + p.x) - p.y)
*/

/*
** Cubic as solved by
** http://www.math.vanderbilt.edu/~schectex/courses/cubic/
*/

float		mobius(vec3 p, float b)
{
	vec3	p2;
	vec2	p3;
	vec4	v;
	vec2	k;

	p2 = pow(p, VEC3(2));
	p3 = p2.xy * p.xy;
	v.x = p2.x + p2.y;
	v.y = 2 * b;
	v.z = p.z * (p2.x * p.y * 3.0 - p3.y);
	v.w = p.x * p2.y * 3.0 - p3.x;
	k.x = (2 * v.z + v.w * (v.x - p2.z + 1)) * (b - .1) - pow(v.x, 2) *
		(v.y + .2);
	k.y = b * v.x * .2 + (v.y - .2) * (v.z + v.w) - v.x * (b + .1) *
		(v.x + p2.z + 1);
	return (pow(k.x, 2) - pow(k.y, 2) * v.x);
}

vec3		mobius_grad(vec3 p, float b)
{
	vec2 q;

	q = VEC2(0.0, 0.01);
	return (VEC3(mobius(p + q.yxx, b) - mobius(p - q.yxx, b),
		mobius(p + q.xyx, b) - mobius(p - q.xyx, b),
		mobius(p + q.xxy, b) - mobius(p - q.xxy, b)));
}

s_res		end_mobius(s_geo_cam gc, float step, s_res ret, vec4 p)
{
	int		i;
	float	tmp;

	step = -step / 2;
	while (++i < 50)
	{
		ret.dst += step;
		p.xyz = gc.cam.pos + ret.dst * gc.cam.ray;
		tmp = p.w;
		p.w = mobius((p.xyz - gc.sp.pos) * 1.5 / gc.sp.bounds, 0.03);
		if (sign(tmp) != sign(p.w))
			step = -step / 2;
	}
	ret.cam = gc.cam;
	ret.mat = gc.sp.mat;
	ret.normal = normalize(-mobius_grad((p.xyz - gc.sp.pos) * 1.5 /
				gc.sp.bounds, 0.01));
	return (ret);
}

s_res		mobius_dst(s_geo sp, s_cam cam, s_res prev)
{
	vec4	p;
	s_res	ret;
	int		i;
	float	step;

	step = 0.05 / 1.5;
	ret.dst = length(cam.pos - sp.pos) <= sp.bounds ?
		0.1 : sphere_dst(sp, cam, prev).dst;
	if (ret.dst < 0 || ret.dst == prev.dst)
		return (prev);
	p.xyz = cam.pos + ret.dst * cam.ray;
	p.w = mobius((p.xyz - sp.pos) * 1.5 / sp.bounds, 0.03);
	i = -1;
	while (++i < INT(sp.bounds) * 60 && p.w <= 0)
	{
		p.w = mobius((p.xyz - sp.pos) * 1.5 / sp.bounds, 0.03);
		ret.dst += step;
		p.xyz = cam.pos + ret.dst * cam.ray;
	}
	if (p.w <= 0)
		return (prev);
	ret = end_mobius(geo_cam(sp, cam), step, ret, p);
	if (prev.dst > 0 && ret.dst > prev.dst)
		return (prev);
	return (ret);
}
