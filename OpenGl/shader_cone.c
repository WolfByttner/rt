/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader_cone.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/24 13:53:38 by fnieto            #+#    #+#             */
/*   Updated: 2016/04/29 17:37:09 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

s_res		circle_dst(s_geo sp, s_cam cam, s_res prev)
{
	s_res	ret;

	ret = plane_dst(sp, cam, prev);
	if (distance(ret.dst * cam.ray + cam.pos, sp.pos) > sp.bounds)
		return (prev);
	return (ret);
}

/*
** a.w is angle. a.xyz is normal (along the cone)
** http://hugi.scene.org/online/hugi24/coding%20graphics%20chris%20dragan%20raytracing%20shapes.htm
** b.x is mmin and b.y is m.max. b.z is radius at base (middle of cylinder)
** To construct a cone, set a.w to 0 and b.z to radius of cylinder
*/

s_res		cone_dst(s_geo sp, s_cam cam, s_res prev)
{
	vec4		v;
	vec4		d;
	vec3		pos;
	s_res		ret;

	pos = cam.pos - sp.pos;
	d.x = dot(cam.ray, sp.a.xyz);
	d.y = dot(pos, sp.a.xyz);
	d.z = (1 + pow(sp.a.w, 2));
	v.x = dot(cam.ray, cam.ray) - d.z * pow(d.x, 2);
	v.y = (dot(cam.ray, pos) - d.z * d.x * d.y) * 2;
	v.z = dot(pos, pos) - d.z * pow(d.y, 2) - pow(sp.b.z, 2);
	d.w = pow(v.y, 2) - 4 * v.x * v.z;
	if (d.w < 0)
		return (prev);
	d.w = sqrt(d.w);
	ret.dst = (-v.y - d.w) / (2 * v.x);
	v.w = d.x * ret.dst + d.y;
	if (ret.dst > 0 && (prev.dst <= 0
		|| (prev.dst > 0 && ret.dst < prev.dst))
		&& (sp.b.x == 0 || sp.b.x <= v.w)
		&& (sp.b.y == 0 || v.w <= sp.b.y))
	{
		ret.normal = normalize(cam.ray * ret.dst + pos - d.z * sp.a.xyz * v.w);
		ret.mat = sp.mat;
		ret.cam = cam;
	}
	else
		ret = prev;
	if (dot(cam.pos, sp.a.xyz) < -sp.b.x)
	ret = (circle_dst(s_geo(0, sp.pos + sp.a.xyz * sp.b.x, sp.a.w == 0 ? sp.b.z
		: abs(sp.a.w * sp.b.x), sp.a, vec4(0), vec4(0), vec4(0), sp.mat), cam,
		ret));
	if (dot(cam.pos, sp.a.xyz) > sp.b.y)
	ret = (circle_dst(s_geo(0, sp.pos + sp.a.xyz * sp.b.y, sp.a.w == 0 ? sp.b.z
		: abs(sp.a.w * sp.b.y), sp.a, vec4(0), vec4(0), vec4(0), sp.mat), cam,
		ret));
	return (ret);
}
