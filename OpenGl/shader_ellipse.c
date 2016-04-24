/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader_ellipse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/24 14:00:26 by fnieto            #+#    #+#             */
/*   Updated: 2016/04/24 14:04:44 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** TODO: put to norm, put vars into vec4s.
** Ellipse
** a.xyz is the x y z
** a.w is pointless // length along unit vector
** http://cudaopencl.blogspot.co.uk/2012/12/ellipsoids-finally-added-to-ray-tracing.html
*/

s_res		ellipse_dst(s_geo sp, s_cam cam, s_res prev)
{
	vec3	dir;
	vec3	centre;
	float	a, b, c;
	float	root;
	s_res	ret;

	centre = (cam.pos - sp.pos) / sp.a.xyz;
	dir = cam.ray / sp.a.xyz;
	a = dot(dir, dir);
	b = dot(dir, centre) * 2;
	c = dot(centre, centre) - 1;
	root = (pow(b, 2) - 4 * a * c);
	if (root <= 0)
		return (prev);
	root = sqrt(root);
	ret.dst = (-b - root) / (2 * a);
	if (ret.dst <= 0)
		ret.dst = (-b + root) / (2 * a);
	if (ret.dst > 0 && (prev.dst <= 0 || ret.dst < prev.dst))
	{
		ret.mat = sp.mat;
		ret.cam = cam;
		ret.normal = normalize(cam.pos + cam.ray * ret.dst - sp.pos);
		return (ret);
	}
	return (prev);
}
