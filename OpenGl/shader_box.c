/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader_box.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeken <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/26 19:33:43 by mdeken            #+#    #+#             */
/*   Updated: 2016/04/29 17:21:09 by mdeken           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 ** sp.pos is the position of the point on the front/left/bottom face
 ** sp.a contains the lenght of each edge along the x, y and z axis
 ** Method:
 ** http://www.cs.cornell.edu/courses/Cs4620/2013fa/lectures/03raytracing1.pdf
 ** Ray-slab intersection chapter
 */

mat3		box_rot(vec4 angle)
{
	mat3	matx;
	mat3	maty;
	mat3	matz;

//	mat4	matx;
//	mat4	maty;
//	mat4	matz;
//	vec4	tmp;

	matx[0] = VEC3(1, 0, 0);
	matx[1] = VEC3(0, cos(angle.x), sin(angle.x));
	matx[1] = VEC3(0, -sin(angle.x), cos(angle.x));

	maty[0] = VEC3(cos(angle.y), 0, -sin(angle.y));
	maty[1] = VEC3(0, 1, 0);
	maty[2] = VEC3(sin(angle.y), 0, cos(angle.y));

	matz[0] = VEC3(cos(angle.z), sin(angle.z), 0);
	matz[1] = VEC3(-sin(angle.z), cos(angle.z), 0);
	matz[2] = VEC3(0, 0, 1);

	matx = inverse(matx);
	maty = inverse(maty);
	matz = inverse(matz);

	return (matx * maty * matz);
}

vec3		box_norm(float tin, vec3 tvin, vec3 tvout)
{
	if (tin == tvin.x)
		return (VEC3(1, 0, 0));
	if (tin == tvin.y)
		return (VEC3(0, 1, 0));
	if (tin == tvin.z)
		return (VEC3(0, 0, 1));
	if (tin == tvout.x)
		return (VEC3(-1, 0, 0));
	if (tin == tvout.y)
		return (VEC3(0, -1, 0));
	if (tin == tvout.z)
		return (VEC3(0, 0, -1));
	return (VEC3(0));
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
	mat3	tmp;

//	sp.pos = sp.pos + (sp.a.xyz / 2);
	tmp = box_rot(sp.b);
//	sp.pos = tmp * sp.pos;
//	ret.cam.ray = tmp * cam.ray;
//	ret.cam.ray = normalize(ret.cam.ray);
	ttmp = (sp.pos - cam.pos) / cam.ray;
	tvout = (sp.pos + sp.a.xyz - cam.pos) / cam.ray;
	tvin = min(ttmp, tvout);
	tvout = max(ttmp, tvout);
	ret.dst = max(max(tvin.x, tvin.y), tvin.z);
	if (min(min(tvout.x, tvout.y), tvout.z) < ret.dst)
		return (prev);
	if (ret.dst > 0 && (prev.dst <= 0 || ret.dst < prev.dst))
	{
		//ret.cam = cam;
		//ret.cam.pos = tmp * cam.pos;
		//ret.cam.ray = tmp * cam.ray;
		//ret.cam.ray = normalize(ret.cam.ray);
		ret.mat = sp.mat;
		ret.normal = box_norm(ret.dst, tvin, tvout);
		return (ret);
	}
	return (prev);
}
