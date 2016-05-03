/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader_goursat.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbyttner <jbyttner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/03 11:55:09 by jbyttner          #+#    #+#             */
/*   Updated: 2016/05/03 18:16:28 by jpiniau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** quick test for different formulas here
*/

float		sum(vec3 p)
{
	return (dot(p, VEC3(1)));
}

/*
** http://mathworld.wolfram.com/GoursatsSurface.html
** mods.xyz are a, b, c in the example
*/

float		goursat(vec3 p, vec3 mods)
{
	vec3	res;
	vec3	p2;

	p2 = pow(p, VEC3(2));
	return (-(sum(pow(p, VEC3(4))) + mods.x * pow(sum(p2), 2) +
				mods.y * sum(p2) + mods.z));
}

vec3		goursat_grad(vec3 p, vec3 mods)
{
	vec2 q;

	q = VEC2(0.0, 0.006);
	return (VEC3(goursat(p + q.yxx, mods) - goursat(p - q.yxx, mods),
		goursat(p + q.xyx, mods) - goursat(p - q.xyx, mods),
		goursat(p + q.xxy, mods) - goursat(p - q.xxy, mods)));
}

s_res		end_goursat(s_geo_cam gc, float step, s_res ret, vec4 p)
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
		p.w = goursat((p.xyz - gc.sp.pos) * 5 / gc.sp.bounds, gc.sp.a.xyz);
		if (sign(step_last) != sign(p.w))
			step = -step / 2;
	}
	ret.cam = gc.cam;
	ret.mat = gc.sp.mat;
	ret.normal = normalize(-goursat_grad((p.xyz - gc.sp.pos) * 5 /
				gc.sp.bounds, gc.sp.a.xyz));
	return (ret);
}

s_res		goursat_dst(s_geo sp, s_cam cam, s_res prev)
{
	vec4	p;
	s_res	ret;
	int		i;
	float	step;
	int		tmp;

	step = 6.0 / 5;
	ret.dst = length(cam.pos - sp.pos) <=
		sp.bounds ? 0.1 : sphere_dst(sp, cam, prev).dst;
	if (ret.dst < 0)
		return (prev);
	p.xyz = cam.pos + ret.dst * cam.ray;
	i = -1;
	while (++i < INT(sp.bounds) * 120)
	{
		if ((p.w = goursat((p.xyz - sp.pos) * 5 / sp.bounds, sp.a.xyz)) > 0)
			break ;
		ret.dst += step;
		p.xyz = cam.pos + ret.dst * cam.ray;
	}
	if (p.w < 0)
		return (prev);
	return (end_goursat(geo_cam(sp, cam), step, ret, p));
}
