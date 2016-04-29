/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader_ellipse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/24 14:00:26 by fnieto            #+#    #+#             */
/*   Updated: 2016/04/29 21:27:13 by jbyttner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Ellipse
** http://mathforum.org/kb/message.jspa?messageID=5345404
*/

vec3		ellipse_norm(s_cam cam, s_res ret, s_geo sp)
{
	vec3	pos;

	pos = 2 * (cam.pos + cam.ray * ret.dst - sp.pos) / pow(sp.a.xyz, VEC3(2));
	return (-normalize(pos));
}

/*
** a.xyz is the x y z
** a.w is pointless // length along unit vector
** http://cudaopencl.blogspot.co.uk/2012/12/ \broken line
** ellipsoids-finally-added-to-ray-tracing.html
*/

s_res		ellipse_dst(s_geo sp, s_cam cam, s_res prev)
{
	vec3	dir;
	vec3	centre;
	s_res	ret;

	centre = (cam.pos - sp.pos) / sp.a.xyz;
	dir = cam.ray / sp.a.xyz;
	if ((ret.dst = solve_quadratic(dot(dir, dir),
			dot(dir, centre) * 2, dot(centre, centre) -1)) == -1)
		return (prev);
	if (ret.dst > 0 && (prev.dst <= 0 || ret.dst < prev.dst))
	{
		ret.mat = sp.mat;
		ret.cam = cam;
		ret.normal = ellipse_norm(cam, ret, sp);
		return (ret);
	}
	return (prev);
}
