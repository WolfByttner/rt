/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader_paint.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/24 13:35:01 by fnieto            #+#    #+#             */
/*   Updated: 2016/04/24 13:38:52 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**function generating all light-object interactions, for the phongong shading.
*/

s_liret		iter_light(s_light light, s_liret liret, s_res res)
{
	s_liret	ret;
	vec3	li;

	ret = liret;
	li = light.pos - liret.cam.pos;
	liret.cam.ray = normalize(li);
	li.z = dot(li, li);
	li.y = raytrace(liret.cam).dst;
	li.x = sqrt(li.z);
	if (li.y < li.x && li.y != -1)
		return (ret);
	li.z = min(1, 1 / li.x * 100);
	ret.diffuse += abs(dot(res.normal, liret.cam.ray)) * light.color * li.z;
	ret.specular += pow(max(dot(reflect(liret.cam.ray, res.normal),
		-liret.cam.ray), 0), 5 / (1 - res.mat.smoothness)) * light.color * li.z;
	return (ret);
}

/*
**material based shading using simple fresnell and blinn phong shading
*/

vec4		paint(s_res res, vec4 lastcol)
{
	int		i;
	s_liret	light;

	light.cam.pos = (res.dst - 0.001) * res.cam.ray + res.cam.pos;
	light.diffuse = VEC4(0);
	light.specular = VEC4(0);
	REP(LINUM, light, iter_light, lights, light, res);
	return (max(mix(light.diffuse * res.mat.color + light.specular, lastcol,
		mix((1 - abs(dot(res.cam.ray, res.normal))) * res.mat.smoothness, 1,
		res.mat.metallic)), AMBIENT));
}
