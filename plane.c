/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/07 17:36:09 by fnieto            #+#    #+#             */
/*   Updated: 2016/03/07 18:31:24 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shader.h"

CL_FUNC t_ret		plane_dst(t_cam cam, t_geo plane, t_ret last)
{
	t_ret	res;
	float	d;

	res.t = dot(plane.pms.s345, cam.ray);
	if (res.t == 0)
		return (last);
	d = dot(plane.pms.s345, plane.pms.s012 - cam.pos);
	res.t = d / res.t;
	if (res.t > 0 && (res.t < last.t || last.t == -1))
	{
		res.normal = plane.pms.s345 * (d > 0 ? -1 : 1);
		res.object = plane;
		return (res);
	}
	return (last);
}
