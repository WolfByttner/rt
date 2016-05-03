/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader_klein.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/24 13:46:54 by fnieto            #+#    #+#             */
/*   Updated: 2016/05/03 18:06:24 by jpiniau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

float		klein(vec3 p)
{
	vec3	p2;
	float	xyz2;

	p2 = pow(p, VEC3(2));
	xyz2 = p2.x + p2.y + p2.z;
	return (-((xyz2 + 2 * p.y - 1) * (pow(xyz2 - 2 * p.y - 1, 2) - 8 * p2.z) +
		16 * p.x * p.z * (xyz2 - 2 * p.y - 1)));
}

vec3		klein_grad(vec3 p)
{
	vec2 q;

	q = VEC2(0.0, 0.006);
	return (VEC3(klein(p + q.yxx) - klein(p - q.yxx),
		klein(p + q.xyx) - klein(p - q.xyx),
		klein(p + q.xxy) - klein(p - q.xxy)));
}

s_res		end_klein(s_geo_cam gc, float step, s_res ret, vec4 p)
{
	int		i;
	float	step_last;

	i = 0;
	step = -step / 2;
	while (i++ < 50)
	{
		ret.dst += step;
		p.xyz = gc.cam.pos + ret.dst * gc.cam.ray;
		step_last = p.w;
		p.w = klein((p.xyz - gc.sp.pos) * 5 / gc.sp.bounds);
		if (sign(step_last) != sign(p.w))
			step = -step / 2;
	}
	ret.cam = gc.cam;
	ret.mat = gc.sp.mat;
	ret.normal = normalize(-klein_grad((p.xyz - gc.sp.pos) * 5 / gc.sp.bounds));
	return (ret);
}

s_res		klein_dst(s_geo sp, s_cam cam, s_res prev)
{
	vec4	p;
	s_res	ret;
	int		i;
	float	step;

	step = 0.05 / 5;
	ret.dst = distance(cam.pos, sp.pos) <= sp.bounds ? 0 :
		sphere_dst(sp, cam, prev).dst;
	if (ret.dst == prev.dst)
		return (prev);
	p.xyz = cam.pos + ret.dst * cam.ray;
	i = -1;
	while (++i < INT(sp.bounds) * 120)
	{
		if ((p.w = klein((p.xyz - sp.pos) * 5 / sp.bounds)) > 0)
			break ;
		ret.dst += step;
		p.xyz = cam.pos + ret.dst * cam.ray;
	}
	if (p.w < 0)
		return (prev);
	ret = end_klein(geo_cam(sp, cam), step, ret, p);
	if ((ret.dst >= prev.dst && prev.dst != -1))
		return (prev);
	return (ret);
}
