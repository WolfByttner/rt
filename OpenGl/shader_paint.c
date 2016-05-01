/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader_paint.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeken <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/30 14:56:01 by mdeken            #+#    #+#             */
/*   Updated: 2016/05/01 20:56:17 by mdeken           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**function generating all light-object interactions, for the phongong shading.
*/

s_liret		iter_light(s_light light, s_liret liret, s_res res)
{
	s_liret	ret;
	vec3	li;
	vec3	pos;

	ret = liret;
	li = light.pos - liret.cam.pos;
	liret.cam.ray = normalize(li);
	li.z = dot(li, li);
	li.y = raytrace(liret.cam).dst;
	li.x = sqrt(li.z);
	if (li.y < li.x && li.y != -1)
		return (ret);
	pos = light.pos - liret.cam.pos;
	li.z = min(1, 1 / li.x * 100);
	ret.diffuse += abs(dot(res.normal, liret.cam.ray)) * light.color * li.z;
	ret.specular += pow(max(dot(reflect(res.cam.ray, res.normal),
		normalize(pos)), 0), length(pos) * 20 * res.mat.metallic) *
		light.color * li.z;
	return (ret);
}



vec4		get_texture(s_mat mat, vec3 pos)
{
	int	checkboard;
	vec3	tmp;

	if (mat.mode_id == CHECKBOARD)
	{
		tmp = pos * mat.mode_param.xyz;
		checkboard = int(floor(tmp.x) + floor(tmp.y) + floor(tmp.z));
			if (checkboard % 2 == 0)
				return (mat.mode_color);
	}
	return (mat.color);
}

/*
**material based shading using simple fresnell and blinn phong shading
*/

vec4		paint(s_res res, vec4 lastcol)
{
	s_liret	light;

	light.cam.pos = (res.dst - 0.001) * res.cam.ray + res.cam.pos;
	res.mat.color = get_texture(res.mat, light.cam.pos);
	light.diffuse = VEC4(0);
	light.specular = VEC4(0);
	REP(LINUM, light, iter_light, lights, light, res);
	return (max(mix(light.diffuse * res.mat.color, lastcol * res.mat.metallic
		+ light.specular, mix((1 - abs(dot(res.cam.ray, res.normal))) *
		res.mat.smoothness, 1, res.mat.metallic)), AMBIENT * res.mat.color));
}
