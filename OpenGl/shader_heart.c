/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader_heart.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbyttner <jbyttner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/02 18:20:20 by jbyttner          #+#    #+#             */
/*   Updated: 2016/05/02 18:59:18 by jbyttner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

float		heart(vec3 p)
{
	vec3	p2;
	float	z3;

	p2 = pow(p, vec3(2));
	z3 = pow(p.z, 3);
	return (-(pow(2 * (p2.x + p2.y) + p2.z - 1, 3)
		- 0.1 * p2.x * z3 - p2.y * z3));
}

vec3		heart_grad(vec3 p)
{
	vec2	q;

	q = vec2(0.0, 0.006);
	return vec3(heart(p + q.yxx) - heart(p - q.yxx),
			heart(p + q.xyx) - heart(p - q.xyx),
			heart(p + q.xxy) - heart(p - q.xxy));
}

s_res		heart_dst(s_geo sp, s_cam cam, s_res prev)
{
	vec3	pos;
	vec4	p;
	s_res	ret;
	int		i;
	float	step;
	float	tmp;

	step = 0.2 / 5;
	pos = cam.pos - sp.pos;
	ret.dst = length(pos) <= sp.bounds ? 0.1 : sphere_dst(sp, cam, prev).dst;
	if (ret.dst >= 0)
	{
		p.xyz = cam.pos + ret.dst * cam.ray;
		p.w = heart((p.xyz - sp.pos) * 5 / sp.bounds);
		i = -1;
		while (++i < int(30 * sp.bounds))
		{
			if (p.w > 0)
				break;
			p.w = heart((p.xyz - sp.pos) * 5 / sp.bounds);
			ret.dst += 0.2 / 5;
			p.xyz = cam.pos + ret.dst * cam.ray;
		}
		if (p.w < 0)
			return (prev);
		i = 0;
		step = -step / 2;
		while (++i < 20)
		{
			ret.dst += step;
			p.xyz = cam.pos + ret.dst * cam.ray;
			tmp = p.w;
			p.w = heart((p.xyz - sp.pos) * 5 / sp.bounds);
			if (sign(tmp) != sign(p.w))
				step = -step / 2;
		}
//		if (p.w < 0)
//			return (prev);
		ret.cam = cam;
		ret.mat = sp.mat;
		ret.normal = normalize(-heart_grad((p.xyz - sp.pos) * 5 / sp.bounds));
		return (ret);
	}
	return (prev);
}
