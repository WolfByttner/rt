/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader_box.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeken <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/26 19:33:43 by mdeken            #+#    #+#             */
/*   Updated: 2016/04/27 18:43:57 by jbyttner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** sp.pos is the position of the point on the front/left/bottom face
** sp.a contains the lenght of each edge along the x, y and z axis
** Method:
** http://www.cs.cornell.edu/courses/Cs4620/2013fa/lectures/03raytracing1.pdf
** Ray-slab intersection chapter
*/

vec3		box_norm(float tin, vec3 tvin, vec3 tvout)
{
	vec3	norm;

	norm = (tin == tvin.x) ? VEC3(1, 0, 0) : norm;
	norm = (tin == tvin.y) ? VEC3(0, 1, 0) : norm;
	norm = (tin == tvin.z) ? VEC3(0, 0, 1) : norm;
	norm = (tin == tvout.x) ? VEC3(-1, 0, 0) : norm;
	norm = (tin == tvout.y) ? VEC3(0, -1, 0) : norm;
	norm = (tin == tvout.z) ? VEC3(0, 0, -1) : norm;
	return (norm);
}

/*
** We do variable juggling to stay within the norm.
** ttmp is tmin and tvout is temporarily tmax.
*/

s_res		box_dst(s_geo sp, s_cam cam, s_res prev)
{
	vec3	tvin;
	vec3	tvout;
	vec3	ttmp;
	s_res	ret;

	ttmp = (sp.pos - cam.pos) / cam.ray;
	tvout = (sp.pos + sp.a.xyz - cam.pos) / cam.ray;
	tvin = min(ttmp, tvout);
	tvout = max(ttmp, tvout);
	ret.dst = max(max(tvin.x, tvin.y), tvin.z);
	if (min(min(tvout.x, tvout.y), tvout.z) < ret.dst)
		return (prev);
	if (ret.dst > 0 && (prev.dst <= 0 || ret.dst < prev.dst))
	{
		ret.cam = cam;
		ret.mat = sp.mat;
		ret.normal = box_norm(ret.dst, tvin, tvout);
		return (ret);
	}
	return (prev);
}
