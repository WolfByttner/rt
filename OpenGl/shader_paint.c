/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader_paint.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeken <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/24 13:35:01 by fnieto            #+#    #+#             */
/*   Updated: 2016/05/04 04:02:36 by fnieto           ###   ########.fr       */
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
	float	occlu;

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
	ret.diffuse += (occlu = max(dot(res.normal, liret.cam.ray), 0)) *
		light.color * li.z;
	ret.specular += pow(max(dot(reflect(res.cam.ray, res.normal),
		normalize(pos)), 0), length(pos) * 20 * res.mat.smoothness) *
		light.color * li.z * res.mat.metallic * step(0, occlu);
	return (ret);
}

s_texmod	get_texture2(s_mat mat, vec3 pos, vec3 normal)
{
	int			val;
	vec3		tmp;
	vec4		v;

	tmp = pos / mat.m_param.xyz;
	if (mat.m_id == RTILES)
	{
		tmp += sin(tmp);
		if (INT(floor(tmp.x) + floor(tmp.y) + floor(tmp.z)) % 2 == 1)
			return (S_TEXMOD(mat.m_color, normal, mat.m_prop.x, mat.m_prop.y));
	}
	if (mat.m_id == RAND)
	{
		tmp = tmp * nrand(floor(tmp * mat.m_param.w) / mat.m_param.w);
		if (INT(floor(tmp.x) + floor(tmp.y) + floor(tmp.z)) % 2 == 1)
			return (S_TEXMOD(mat.m_color, normal, mat.m_prop.x, mat.m_prop.y));
	}
	if (mat.m_id == PERLIN)
	{
		v.x = noise(tmp, 5);
		return (S_TEXMOD(mix(mat.color, mat.m_color, v.x), normal,
			mix(mat.smoothness, mat.m_prop.x, v.x), mix(mat.metallic,
				mat.m_prop.y, v.x)));
	}
	return (S_TEXMOD(mat.color, normal, mat.smoothness, mat.metallic));
}

s_texmod	get_texture(s_mat mat, vec3 pos, vec3 normal)
{
	int			val;
	vec3		tmp;
	vec4		v;

	tmp = pos / mat.m_param.xyz;
	if (mat.m_id == CHECKBOARD)
	{
		if (INT(floor(tmp.x) + floor(tmp.y) + floor(tmp.z)) % 2 == 1)
			return (S_TEXMOD(mat.m_color, normal, mat.m_prop.x, mat.m_prop.y));
		return (S_TEXMOD(mat.color, normal, mat.smoothness, mat.metallic));
	}
	if (mat.m_id == BUMP)
	{
		tmp = VEC3(sin(tmp.x), 0, cos(tmp.z));
		v.x = length(tmp);
		return (S_TEXMOD(mat.color, normalize(normal + mat.m_param.w * tmp),
			mat.smoothness * v.x, mat.metallic * v.x));
	}
	if (mat.m_id == WAVE)
	{
		tmp = floor(tmp + sin(tmp.zyx));
		if (INT(tmp.x + tmp.y + tmp.z) % 2 == 1)
			return (S_TEXMOD(mat.m_color, normal, mat.m_prop.x, mat.m_prop.y));
	}
	return (get_texture2(mat, pos, normal));
}

/*
**material based shading using simple fresnell and blinn phong shading
*/

vec4		paint(s_res res, vec4 lastcol)
{
	s_liret		light;
	s_texmod	mod;

	light.cam.pos = (res.dst - 0.1) * res.cam.ray + res.cam.pos;
	mod = get_texture(res.mat, light.cam.pos, res.normal);
	light.diffuse = VEC4(0);
	light.specular = VEC4(0);
	res.mat.color = mod.color;
	res.normal = mod.normal;
	res.mat.smoothness = mod.smoothness;
	res.mat.metallic = mod.metallic;
	REP(LINUM, light, iter_light, lights, light, res);
	return (max(mix(light.diffuse * mod.color, lastcol * res.mat.metallic
		+ light.specular, mix((1 - abs(dot(res.cam.ray, res.normal))) *
		res.mat.smoothness, 1, res.mat.metallic)), AMBIENT * res.mat.color));
}
