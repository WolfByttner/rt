/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader_mobius.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/24 13:42:58 by fnieto            #+#    #+#             */
/*   Updated: 2016/04/24 16:24:22 by fnieto           ###   ########.fr       */
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
**
*/

/*
** Cubic as solved by
** http://www.math.vanderbilt.edu/~schectex/courses/cubic/
*/

s_res           mobius_dst(s_geo sp, s_cam cam, s_res prev)
{
	float           a, b, c, d;
	float           p, q, r;
	float           rinner, router;
	float           ddot, dxydot, dpdot, dpxydot, pdot, pxydot;
	s_res           ret;

	ddot = dot(cam.pos, cam.pos);
	dxydot = dot(cam.pos.xy, cam.pos.xy);
	dpxydot = dot(cam.pos.xy, cam.ray.xy);
	dpdot = dot(cam.pos, cam.ray);
	pdot = dot(cam.ray, cam.ray);
	pxydot = dot(cam.ray.xy, cam.ray.xy);
	a = ddot * cam.pos.y - 2 * dxydot * cam.pos.z;
	b = ddot * cam.ray.y + 2 * (cam.pos.y * dpdot - cam.ray.z * dxydot
			- cam.pos.x * cam.pos.z - 2 * dpxydot);
	c = cam.pos.y * pdot + 2 * (dpdot * cam.ray.y
			- cam.ray.z * (cam.pos.x * 2 * dpxydot)
			- cam.pos.z * (pxydot + cam.ray.x))
		- cam.ray.y;
	d = cam.ray.y * pdot - 2 * cam.ray.z * (pxydot + cam.ray.x) - cam.ray.y;
	p = -b / (3 * a);
	q = pow(p, 3) + (b * c - 3 * a * d) / (6 * pow(a, 2));
	r = c / (3 * a);
	// TODO: Check if these are actually the correct tests
	rinner = pow(q, 2) + pow((r - pow(b, 2)), 3);
	if (rinner <= 0)
		return (prev);
	rinner = sqrt(rinner);
	router = q - rinner;
	if (router < 0)
		return (prev);
	router = pow(router, 1 / 3);
	ret.dst = router;
	router = q + rinner;
	if (router < 0)
		return (prev);
	router = pow(router, 1 / 3);
	ret.dst += router;
	ret.dst += p;
	if (ret.dst > 0 && (prev.dst <= 0 || ret.dst < prev.dst))
	{
		ret.mat = sp.mat;
		ret.cam = cam;
		ret.normal = vec3(0, 1, 0);
		return (ret);
	}
	return (prev);
}
