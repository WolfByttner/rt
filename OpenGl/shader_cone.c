/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader_cone.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/24 13:53:38 by fnieto            #+#    #+#             */
/*   Updated: 2016/04/24 16:57:26 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** a.w is angle. a.xyz is normal (along the cone)
** http://hugi.scene.org/online/hugi24/coding%20graphics%20chris%20dragan%20raytracing%20shapes.htm
** b.x is mmin and b.y is m.max. b.z is radius at base (middle of cylinder)
** To construct a cone, set a.w to 0 and b.z to radius of cylinder
*/

s_res		cone_dst(s_geo sp, s_cam cam, s_res prev)
{
	vec4		v;
	float		root;
	float		rdot, pdot, opa2;
	vec3		pos;
	s_res		ret;

	pos = cam.pos - sp.pos;
	rdot = dot(cam.ray, sp.a.xyz);
	pdot = dot(pos, sp.a.xyz);
	opa2 = (1 + pow(sp.a.w, 2));
	v.x = dot(cam.ray, cam.ray) - opa2 * pow(rdot, 2);
	v.y = (dot(cam.ray, pos) - opa2 * rdot * pdot) * 2;
	v.z = dot(pos, pos) - opa2 * pow(pdot, 2) - pow(sp.b.z, 2);
	root = pow(v.y, 2) - 4 * v.x * v.z;
	if (root < 0)
		return (prev);
	root = sqrt(root);
	ret.dst = (-v.y - root) / (2 * v.x);
	if (ret.dst < 0)
		ret.dst = (-v.y + root) / (2 * v.x);
	v.w = rdot * ret.dst + pdot;
	if ((sp.b.x != 0 && sp.b.x > v.w) || (sp.b.y != 0 && v.w > sp.b.y))
	{
		ret.dst = (-v.y + root) / (2 * v.x);
		if (ret.dst < 0)
			return (prev);
		v.w = rdot * ret.dst + pdot;
		if ((sp.b.x == 0 || sp.b.x <= v.w) && (sp.b.y == 0 || v.w <= sp.b.y))
		{
			if (rdot == 0)
				return (prev);
			else
			{
				ret.dst = dot(pos, -sp.a.xyz) / rdot;
				if (ret.dst < 0)
					return (prev);
				ret.normal = -sp.a.xyz;
				ret.mat = sp.mat;
				ret.cam = cam;
				return (ret);
			}
		}
		else
			return (prev);
	}
	if (ret.dst > 0 && (prev.dst <= 0
		|| (prev.dst > 0 && ret.dst < prev.dst))
		&& (sp.b.x == 0 || sp.b.x <= v.w)
		&& (sp.b.y == 0 || v.w <= sp.b.y))
	{
		ret.normal = normalize(cam.ray * ret.dst + pos - opa2 * sp.a.xyz * v.w);
		ret.mat = sp.mat;
		ret.cam = cam;
		return (ret);
	}
	return (prev);
}
