/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader_sphere.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/24 14:06:00 by fnieto            #+#    #+#             */
/*   Updated: 2016/04/27 20:27:34 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

s_res		sphere_dst(s_geo sp, s_cam cam, s_res prev)
{
	s_res		ret;
	vec3		rc;
	float		b;
	float		d;

	rc = cam.pos - sp.pos;
	b = dot(cam.ray, rc);
	d = pow(b, 2) - dot(rc, rc) + pow(sp.bounds, 2);
	b = -b - sqrt(abs(d));
	ret.dst = mix(-1, b, step(0, min(b, d)));
	if (ret.dst > 0 && (prev.dst <= 0 || (prev.dst > 0 && ret.dst < prev.dst)))
	{
		ret.mat = sp.mat;
		ret.cam = cam;
		ret.normal = (-normalize(sp.pos - (cam.pos + cam.ray * ret.dst)));
		return (ret);
	}
	return (prev);
}
