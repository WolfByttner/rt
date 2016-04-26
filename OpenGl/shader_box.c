/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader_box.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeken <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/26 19:33:43 by mdeken            #+#    #+#             */
/*   Updated: 2016/04/26 19:52:50 by mdeken           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 **sp.pos is the position of the point on the front/left/bottom face
 **sp.a contains the lenght of each edge along the x, y and z axis
 **Method: http://www.cs.cornell.edu/courses/Cs4620/2013fa/lectures/03raytracing1.pdf Ray-slab intersection chapter
 */


vec3		box_norm(float tin, vec3 tvin, vec3 tvout)
{
	vec3 norm;

	norm = (tin == tvin.x) ? VEC3(1, 0, 0) : norm;
	norm = (tin == tvin.y) ? VEC3(0, 1, 0) : norm;
	norm = (tin == tvin.z) ? VEC3(0, 0, 1) : norm;
	norm = (tin == tvout.x) ? VEC3(-1, 0, 0) : norm;
	norm = (tin == tvout.y) ? VEC3(0, -1, 0) : norm;
	norm = (tin == tvout.z) ? VEC3(0, 0, -1) : norm;
	return (norm);
}

s_res		box_dst(s_geo sp, s_cam cam, s_res prev)
{
	float	tin, tout;
	vec3	tmin, tmax, tvin, tvout;
	s_res	ret;
	vec3	inv_ray;

	inv_ray = 1 / cam.ray;
	tmin = (sp.pos - cam.pos) * inv_ray;
	tmax = (sp.pos + sp.a.xyz - cam.pos) * inv_ray;
	tvin = min(tmin, tmax);
	tvout = max(tmin, tmax);
	tin = max(max(tvin.x, tvin.y), tvin.z);
	tout = (min(min(tvout.x, tvout.y), tvout.z));
	if (tout < tin)
		return (prev);
	if (tin > 0 && (prev.dst <= 0 || tin < prev.dst))
	{
		ret.dst = tin;
		ret.cam = cam;
		ret.mat = sp.mat;
		ret.normal = box_norm(tin, tvin, tvout);
		return (ret);
	}
	return (prev);
}
