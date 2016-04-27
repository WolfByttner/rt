/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader_plane.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/24 13:48:42 by fnieto            #+#    #+#             */
/*   Updated: 2016/04/27 20:23:51 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** returns an intersection to the plane or the ast result if failed
** sp.a = the normal of the plane
*/

s_res	plane_dst(s_geo sp, s_cam cam, s_res prev)
{
	s_res			ret;
	vec3			rc;
	float			tmp;

	ret.normal = -sp.a.xyz;
	tmp = dot(cam.ray, ret.normal);
	if (tmp == 0)
		return (prev);
	rc = sp.pos.xyz - cam.pos;
	ret.dst = dot(rc, ret.normal) / tmp;
	if (ret.dst > 0 && (prev.dst <= 0 || (prev.dst > 0 && ret.dst < prev.dst)))
	{
		ret.mat = sp.mat;
		ret.cam = cam;
		return (ret);
	}
	return (prev);
}
