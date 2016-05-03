/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader_klein.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/24 13:46:54 by fnieto            #+#    #+#             */
/*   Updated: 2016/05/03 00:00:39 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

float		klein(vec3 p)
{
	vec3	p2;
	float	xyz2;

	p2 = pow(p, VEC3(2));
	xyz2 = p2.x + p2.y + p2.z;
	return (-((xyz2 + 2 * p.y - 1) * (pow(xyz2 - 2 * p.y -1, 2) - 8 * p2.z) +
		16 * p.x * p.z * (xyz2 - 2 * p.y - 1)));
}


vec3		klein_grad(vec3 p) {
	vec2 q;

	q = VEC2(0.0, 0.006);
	return VEC3(klein(p + q.yxx) - klein(p - q.yxx),
		klein(p + q.xyx) - klein(p - q.xyx),
		klein(p + q.xxy) - klein(p - q.xxy));
}

s_res		klein_dst(s_geo sp, s_cam cam, s_res prev)
{
	vec4	p;
	s_res	ret;
	int		i;
	float	step;
	float	step_last;

	step = 0.05 / 5;
	ret.dst = length(cam.pos - sp.pos) <= sp.bounds ? 0 :
		sphere_dst(sp, cam, prev).dst;
	if (ret.dst >= 0 && ret.dst != prev.dst)
	{
		p.xyz = cam.pos + ret.dst * cam.ray;
		i = -1;
		while (++i < int(120 * sp.bounds))
		{
			if ((p.w = klein((p.xyz - sp.pos) * 5 / sp.bounds)) > 0)
				break ;
			ret.dst += step;
			p.xyz = cam.pos + ret.dst * cam.ray;
		}
		if (p.w < 0)
			return (prev);
		i = 0;
		step = -step / 2;
		while (i++ < 50)
		{
			ret.dst += step;
			p.xyz = cam.pos + ret.dst * cam.ray;
			step_last = p.w;
			p.w = klein((p.xyz - sp.pos) * 5 / sp.bounds);
			if (sign(step_last) != sign(p.w))
				step = -step / 2;
		}
		if (prev.dst > 0 && ret.dst > prev.dst)
			return (prev);
		ret.cam = cam;
		ret.mat = sp.mat;
		ret.normal = normalize(-klein_grad((p.xyz - sp.pos) * 5 / sp.bounds));
		return (ret);
	}
	return (prev);
}
