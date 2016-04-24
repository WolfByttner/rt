/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/24 12:35:26 by fnieto            #+#    #+#             */
/*   Updated: 2016/04/24 17:02:47 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**Makes a rotation matrix from x and z rotation axis
*/

mat3	make_matrix(vec4 sins)
{
	return (MAT3(1, 0, 0, 0, sins.w, -sins.z, 0, sins.z, sins.w)
		* MAT3(sins.y, 0, sins.x, 0, 1, 0, -sins.x, 0, sins.y));
}

/*
**makes a cubes face, rotates it by the rotation matrix and interpolates the
**vector on the surface from the uv coodinates
**uv: the axis of the screen [0; 1]
*/

vec3	make_cam_ray(vec2 uv)
{
	mat3	transform;
	vec2	camrot;
	vec2	ratio;

	camrot = VEC2(iCameraRotation.x, clamp(iCameraRotation.y,
		-PI / 2, PI / 2));
	ratio = iResolution.xy / FLOAT(iResolution.y);
	transform = make_matrix(
		VEC4(sin(camrot.x), cos(camrot.x), sin(camrot.y), cos(camrot.y)));
	return (normalize(mix(mix(VEC3(-1, -1, 1) * transform *
		VEC3(iCameraZoom * ratio, 1), VEC3(1, -1, 1) * transform *
		VEC3(iCameraZoom * ratio, 1), uv.x), mix(VEC3(-1, 1, 1) * transform *
		VEC3(iCameraZoom * ratio, 1), VEC3(1, 1, 1) * transform *
		VEC3(iCameraZoom * ratio, 1), uv.x), uv.y)));
}

/*
**the glsl main fuction, has to set the color of its assigned pixel.
**it will path trace through the scene with "iterate(cam)"
**he will then use renderlights to simulate the lights being physical.
*/

void	main(void)
{
	s_cam	cam;
	vec2	uv;
	vec4	col;
	s_res	tmp;

	uv = gl_FragCoord.xy / iResolution;
	cam.pos = iCameraPosition;
	cam.pos.z -= 10;
	cam.ray = make_cam_ray(uv);
	tmp = iterate(cam);
	if (tmp.dst != -1)
	{
		col = tmp.color;
		tmp.cam = cam;
		col += render_lights(tmp);
		outcol = VEC4(col.xyz, 1);
	}
	else
		outcol = VEC4(render_lights(tmp).xyz, 1);
}
