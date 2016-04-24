/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader_render_lights.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/24 13:31:08 by fnieto            #+#    #+#             */
/*   Updated: 2016/04/24 13:34:50 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**fuction generating the pecular shine of the lights
*/

vec4		iter_spec(s_light light, vec4 specular, s_res res)
{
	vec3	lpos;
	vec3	li;
	vec4	ret;

	ret = specular;
	lpos = light.pos - res.cam.pos;
	li.z = dot(lpos, lpos);
	li.x = sqrt(li.z);
	if (li.x > res.dst && res.dst > 0)
		return (ret);
	li.z = min(1, 1 / li.x * 100);
	ret += pow(max(dot(normalize(lpos), res.cam.ray), 0), length(lpos) * 50)
		* light.color * li.z;
	return (ret);
}

/*
**function macro looping throught the lights to generate specularity for the
**pretty lights
*/

vec4		render_lights(s_res res)
{
	vec4	specular;

	specular = VEC4(0);
	REP(LINUM, specular, iter_spec, lights, specular, res);
	return (specular);
}
