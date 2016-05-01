/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader_klein.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/24 13:46:54 by fnieto            #+#    #+#             */
/*   Updated: 2016/05/01 20:39:39 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

float		klein(vec3 p)
{
	vec3	p2;
	float	xyz2;

	p2 = pow(p, vec3(2));
	xyz2 = p2.x + p2.y + p2.z;
	return (-((xyz2 + 2 * p.y - 1) * (pow(xyz2 - 2 * p.y -1, 2) - 8 * p2.z) +
		16 * p.x * p.z * (xyz2 - 2 * p.y - 1)));
}

vec3		klein_grad(vec3 p) {
	vec2 q;

	q = vec2(0.0, 0.01);
	return vec3(klein(p + q.yxx) - klein(p - q.yxx),
		klein(p + q.xyx) - klein(p - q.xyx),
		klein(p + q.xxy) - klein(p - q.xxy));
}
/*
**TODO: actually making it.
*/

s_res		klein_dst(s_geo sp, s_cam cam, s_res prev)
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
		p.w = klein(p.xyz);
		if (p.w > 0)
			ret.dst += 0.1;
		p.xyz = cam.pos + ret.dst * cam.ray;
		p.w = klein(p.xyz);
		if (p.w > 0)
		i = -1;
		while (++i < 1024)
		{
			if (p.w > 0)
				break;
			p.w = klein(p.xyz);
			ret.dst += 0.01;
			p.xyz = cam.pos + ret.dst * cam.ray;
		}
		if (p.w <= 0)
			return (prev);
		ret.cam = cam;
		ret.mat = sp.mat;
		ret.normal = normalize(-klein_grad(p.xyz));
		return (ret);
	}
	return (prev);
}
