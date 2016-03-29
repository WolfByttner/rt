/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fragment.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbyttner <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/26 21:44:17 by jbyttner          #+#    #+#             */
/*   Updated: 2016/03/29 18:48:37 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#version 330 core

# define PI 3.1415926535897932384626433832795

# define	IGNORE		0
# define	SPHERE		1
# define	ELLYPSE		2
# define	CONE		3
# define	CYLINDER	4
# define	BOX			5
# define	PLANE		6
# define	KLEIN		7
# define	MOBIUS		8

# define	ITERATIONS	13

struct			s_cam
{
	vec3		pos;
	vec3		ray;
};

struct			s_mat
{
	vec4		color;
	float		metallic;
	float		smoothness;
	vec2		opacity;
};

struct			s_geo
{
	int			type;
	vec3		pos;
	float		bounds;
	vec4		a;
	vec4		b;
	vec4		c;
	vec4		d;
	s_mat		mat;
};

struct			s_light
{
	vec4		color;
	vec3		pos;
};

struct			s_res
{
	float		dst;
	vec3		normal;
	s_cam		cam;
	s_mat		mat;
};

uniform ivec2 iResolution;
uniform vec3 iCameraPosition = vec3(0, 0, 0);
uniform vec2 iCameraRotation = vec2(0, 0);
uniform float iCameraZoom = 1;
uniform float iGlobalTime = 0;

layout (location = 0) out vec4 outcol;

vec3		sphere_norm(s_cam cam, s_res ret, s_geo object)
{
	return (-normalize(object.pos - (cam.pos + cam.ray * ret.dst)));
}

s_res		sphere_dst(s_cam cam, s_geo sp, s_res prev)
{
	s_res		ret;
	vec3		rc;
	float		b, d, t;

	rc = cam.pos - sp.pos;
	b = dot(cam.ray, rc);
	d = pow(b, 2) - dot(rc, rc) + pow(sp.bounds, 2);
	t = -b - sqrt(abs(d));
	ret.dst = mix(-1, t, step(0, min(t,d)));
	if ((ret.dst > 0 && prev.dst <= 0) ||
			(ret.dst > 0 && prev.dst > 0 && ret.dst < prev.dst))
	{
		ret.mat = sp.mat;
		ret.normal = sphere_norm(cam, ret, sp);
		return (ret);
	}
	return (prev);
}

vec4		paint(s_res res, s_light[1] lights)
{
	int		i;
	vec4	diffuse;
	vec4	specular;
	s_cam	newcam;
	vec3	li;
	s_cam cam = res.cam;

	newcam.pos = (res.dst - 0.001) * cam.ray + cam.pos;
	i = -1;
	while (++i < lights.length())
	{
		li = lights[i].pos - (newcam.pos);
		newcam.ray = normalize(li);
		li.z = dot(li, li);
		//li.y = raytrace(newcam, objs, sz.z).t;
		li.x = sqrt(li.z);
		//if (li.y < li.x && li.y != -1)
		//	continue;
		li.z = min(1, 1 / li.x * 100);
		diffuse += max(dot(res.normal, newcam.ray), 0) * lights[i].color * li.z;
		specular += pow(max(dot(reflect(-newcam.ray, res.normal), -cam.ray), 0),
			10) * res.mat.smoothness * lights[i].color * li.z;
	}
	return (diffuse * res.mat.color * (1 - res.mat.smoothness) + specular);
}

vec4		render_lights(s_res res, s_light[1] lights)
{
	int		i;
	vec4	specular;
	vec3	li, light;

	specular = vec4(0);
	i = -1;
	while (++i < lights.length())
	{
		light = lights[i].pos - res.cam.pos;
		li.z = dot(light, light);
		li.x = sqrt(li.z);
		//if (li.x > res.dst && res.dst > 0)
		//	continue;
		li.z = min(1, 1 / li.x * 100);
		specular += pow(max(dot(reflect(-newcam.ray, res.normal), -cam.ray), 0),
			10) * res.mat.smoothness * lights[i].color * li.z;
	}
	return (specular);

}

/*
 ** spherical to euclidian coordinates transformation
 */

vec3		make_view_vector(vec2 uv)
{
	return (normalize(
				vec3(sin(uv.y) * cos(uv.x), sin(uv.y) * sin(uv.x), cos(uv.y))
				).xzy);
}

void		main()
{
	s_cam	cam;
	vec2	uv;
	vec2	fov;

	uv = -(gl_FragCoord.xy / iResolution - 0.5) *
		iResolution.xy / float(iResolution.y) * iCameraZoom * PI / 2 -
		iCameraRotation * PI + vec2(-iGlobalTime - PI, 0) + PI / 2;
	cam.pos = iCameraPosition + vec3(sin(iGlobalTime), 0, cos(iGlobalTime)) * 30;
	cam.ray = make_view_vector(uv);

	s_mat ms[1] = s_mat[1](s_mat(vec4(1), 0.5, 0.5, vec2(0)));

	s_light lights[] = s_light[](
			s_light(vec4(1, 1, 1, 1), vec3(0, -2, 0))
			);

	s_geo geos[] = s_geo[](
			s_geo(SPHERE, vec3(0, 0, 0), 1, vec4(0), vec4(0), vec4(0), vec4(0), ms[0]),
			s_geo(SPHERE, vec3(-2, 0, 0), 1, vec4(0), vec4(0), vec4(0), vec4(0), ms[0]),
			s_geo(SPHERE, vec3(2, 0, 0), 1, vec4(0), vec4(0), vec4(0), vec4(0), ms[0])
			);

	s_res tmp;
	tmp.dst = -1;
	tmp.cam = cam;
	tmp = sphere_dst(cam, geos[0], tmp);
	tmp = sphere_dst(cam, geos[1], tmp);
	tmp = sphere_dst(cam, geos[2], tmp);

	if (tmp.dst != -1)
	{
		vec4 col = paint(tmp, lights);
		col += render_lights(tmp, lights);
		outcol = vec4(col.xyz, 1);
	}
	else
		outcol = vec4(render_lights(tmp, lights).xyz, 1);
}
