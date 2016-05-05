/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader_eight.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbyttner <jbyttner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/05 13:23:59 by jbyttner          #+#    #+#             */
/*   Updated: 2016/05/05 13:24:50 by jbyttner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Eight as solved by
** http://mathworld.wolfram.com/EightSurface.html
*/

float		eight(vec3 p, float b)
{
	vec3	p2;

	p2 = pow(p, VEC3(2));
	return (-(4 * pow(p.y, 4) + 2 * (p2.x + p2.z - 4 * p2.y)));
}

vec3		eight_grad(vec3 p, float b)
{
	vec2	q;

	q = VEC2(0.0, 0.01);
	return (VEC3(eight(p + q.yxx, b) - eight(p - q.yxx, b),
		eight(p + q.xyx, b) - eight(p - q.xyx, b),
		eight(p + q.xxy, b) - eight(p - q.xxy, b)));
}

s_res		end_eight(s_geo_cam gc, float step, s_res ret, vec4 p)
{
	int		i;
	float	tmp;

	step = -step / 2;
	while (++i < 50)
	{
		ret.dst += step;
		p.xyz = gc.cam.pos + ret.dst * gc.cam.ray;
		tmp = p.w;
		p.w = eight((p.xyz - gc.sp.pos) * 5 / gc.sp.bounds, 0.03);
		if (sign(tmp) != sign(p.w))
			step = -step / 2;
	}
	ret.cam = gc.cam;
	ret.mat = gc.sp.mat;
	ret.normal = normalize(-eight_grad((p.xyz - gc.sp.pos) * 5 /
				gc.sp.bounds, 0.01));
	return (ret);
}

s_res		eight_dst(s_geo sp, s_cam cam, s_res prev)
{
	vec4	p;
	s_res	ret;
	int		i;
	float	step;

	step = 0.2 / 5;
	ret.dst = length(cam.pos - sp.pos) <= sp.bounds ?
		0.1 : sphere_dst(sp, cam, prev).dst;
	if (ret.dst < 0 || ret.dst == prev.dst)
		return (prev);
	p.xyz = cam.pos + ret.dst * cam.ray;
	p.w = eight((p.xyz - sp.pos) * 5 / sp.bounds, 0.03);
	i = -1;
	while (++i < INT(sp.bounds) * 120 && p.w <= 0)
	{
		p.w = eight((p.xyz - sp.pos) * 5 / sp.bounds, 0.03);
		ret.dst += step;
		p.xyz = cam.pos + ret.dst * cam.ray;
	}
	if (p.w <= 0)
		return (prev);
	ret = end_eight(geo_cam(sp, cam), step, ret, p);
	if (prev.dst > 0 && ret.dst > prev.dst)
		return (prev);
	return (ret);
}
