/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader_mobius.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/24 13:42:58 by fnieto            #+#    #+#             */
/*   Updated: 2016/05/01 17:56:10 by fnieto           ###   ########.fr       */
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

float mobius(vec3 p, float b) {
	vec3	p2;
	vec2	p3;
	vec4	v;
	vec2	k;

	p2 = pow(p, vec3(2));
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

vec3 grad(vec3 p, float b) {
	vec2 q;

	q = vec2(0.0, 0.01);
	return vec3(mobius(p + q.yxx, b) - mobius(p - q.yxx, b),
		mobius(p + q.xyx, b) - mobius(p - q.xyx, b),
		mobius(p + q.xxy, b) - mobius(p - q.xxy, b));
}

s_res			mobius_dst(s_geo sp, s_cam cam, s_res prev)
{
	vec3	pos;
	vec4	p;
	s_res	ret;
	int		i;

	pos = cam.pos - sp.pos;
	ret.dst = 0;
	if (length(pos) <= sp.bounds ||
		(ret.dst = sphere_dst(sp, cam, prev).dst) > 0)
	{
		p.xyz = cam.pos + ret.dst * cam.ray;
		p.w = mobius(p.xyz, 0.03);
		if (p.w > 0)
			ret.dst += 0.1;
		p.w = mobius(p.xyz, 0.03);
		if (p.w > 0)
		i = -1;
		while (++i < 512)
		{
			if (p.w > 0)
				break;
			p.w = mobius(p.xyz, 0.03);
			ret.dst += 0.005;
			p.xyz = cam.pos + ret.dst * cam.ray;
		}
		if (p.w <= 0)
			return (prev);
		ret.cam = cam;
		ret.mat = sp.mat;
		ret.normal = normalize(-grad(p.xyz, 0.01));
		return (ret);
	}
	return (prev);
}
