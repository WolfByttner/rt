/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/06 14:40:49 by fnieto            #+#    #+#             */
/*   Updated: 2016/03/06 16:32:37 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shader.h"

CL_FUNC t_ret		sphere_dst(t_cam cam, t_geo sp, t_ret prev)
{
	t_ret		ret;
	float3		rc;

	rc = cam.pos-sp.pms.s012;
	float c = dot(rc, rc) - sp.pms.s3*sp.pms.s3;
	float b = dot(cam.ray, rc);
	float d = b*b - c;
	float t = -b - sqrt(fabs(d));
	float st = step((float)(0.0), min(t,d));
	float m = mix((float)(-1.0), t, st);
	ret.t = m;
	if ((ret.t > 0 && prev.t <= 0) || (ret.t > 0 && prev.t > 0 && ret.t < prev.t))
	{
		ret.object = sp;
		return (ret);
	}
	ret = prev;
	return (ret);
}

CL_FUNC float3		sphere_norm(t_cam cam, t_ret ret)
{
	return (-normalize(ret.object.pms.s012 - (cam.pos+cam.ray*ret.t)));
}

