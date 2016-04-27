/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader_raytrace.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/24 13:39:27 by fnieto            #+#    #+#             */
/*   Updated: 2016/04/27 20:26:55 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**dynamic dispatch function used for selecting the right object from its ID
**please sort from most used to least used.
*/

s_res		obj_dst(s_geo obj, s_cam cam, s_res prev)
{
	if (obj.type == SPHERE)
		return (sphere_dst(obj, cam, prev));
	if (obj.type == ELLIPSE)
		return (ellipse_dst(obj, cam, prev));
	if (obj.type == CONE)
		return (cone_dst(obj, cam, prev));
	if (obj.type == CYLINDER)
		return (cylinder_dst(obj, cam, prev));
	if (obj.type == BOX)
		return (box_dst(obj, cam, prev));
	if (obj.type == PLANE)
		return (plane_dst(obj, cam, prev));
	if (obj.type == MOBIUS)
		return (mobius_dst(obj, cam, prev));
	return (prev);
}

/*
**itareating through all objects in a macro expanding loop
*/

s_res		raytrace(s_cam cam)
{
	int		i;
	s_res	res;

	res.dst = -1;
	res.cam = cam;
	REP(GEONUM, res, obj_dst, geos, cam, res);
	return (res);
}
