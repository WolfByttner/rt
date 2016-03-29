/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fragment.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbyttner <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/26 21:44:17 by jbyttner          #+#    #+#             */
/*   Updated: 2016/03/29 22:09:58 by fnieto           ###   ########.fr       */
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
# define	AMBIENT		(vec4(0.06, 0.04, 0.08, 0))

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

 s_mat ms[] = s_mat[](s_mat(vec4(1), 0.9, 0.8, vec2(0)));

s_light lights[] = s_light[](
	s_light(vec4(1), vec3(cos(-iGlobalTime) * 10, 0, sin(-iGlobalTime) * 10)),
	s_light(vec4(1), vec3(-cos(-iGlobalTime) * 10, 0, -sin(-iGlobalTime) * 10))
	);

s_geo geos[] = s_geo[](
	s_geo(SPHERE, vec3(0, 0, 0), 2, vec4(0), vec4(0), vec4(0), vec4(0), ms[0]),
	s_geo(SPHERE, vec3(-3, 0, 0), 1, vec4(0), vec4(0), vec4(0), vec4(0), ms[0]),
	s_geo(SPHERE, vec3(3, 0, 0), 1, vec4(0), vec4(0), vec4(0), vec4(0), ms[0])
	);

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
	if (ret.dst > 0 && (prev.dst <= 0 || (prev.dst > 0 && ret.dst < prev.dst)))
	{
		ret.mat = sp.mat;
		ret.cam = cam;
		ret.normal = sphere_norm(cam, ret, sp);
		return (ret);
	}
	return (prev);
}

s_res		raytrace(s_cam cam)
{
	int		i;
	s_res	res;

	res.dst = -1;
	res.cam = cam;
	i = -1;
	while (++i < geos.length())
	{
	//	if (geos[i].type == SPHERE)
			res = sphere_dst(cam, geos[i], res);
	}
	return (res);
}

vec4		paint(s_res res)
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
		li.y = raytrace(newcam).dst;
		li.x = sqrt(li.z);
		if (li.y < li.x && li.y != -1)
			continue;
		li.z = min(1, 1 / li.x * 100);
		diffuse += max(dot(res.normal, newcam.ray), 0) * lights[i].color * li.z;
		specular += pow(max(dot(reflect(-newcam.ray, res.normal), -cam.ray), 0),
				1 / (1 - res.mat.smoothness)) * lights[i].color * li.z;
	}
	return (max(diffuse * res.mat.color * (1 - res.mat.smoothness), AMBIENT)
			+ specular * res.mat.smoothness);
}

vec4		render_lights(s_res res)
{
	int		i;
	vec4	specular;
	vec3	li, light;

	i = -1;
	while (++i < lights.length())
	{
		light = lights[i].pos - res.cam.pos;
		li.z = dot(light, light);
		li.x = sqrt(li.z);
		if (li.x > res.dst && res.dst > 0)
			continue;
		li.z = min(1, 1 / li.x * 100);
		specular += pow(max(dot(-normalize(light), -res.cam.ray), 0),
				10000) * lights[i].color * li.z;
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
		iResolution.xy / float(iResolution.y) * iCameraZoom * PI * 0.5 -
		iCameraRotation * PI + PI * 0.5;
	cam.pos = iCameraPosition;
	cam.pos.z = -10;
	cam.ray = make_view_vector(uv);

	s_res tmp = raytrace(cam);
	if (tmp.dst != -1)
	{
		vec4 col = paint(tmp);
		tmp.cam = cam;
		col += render_lights(tmp);
		outcol = vec4(col.xyz, 1);
	}
	else
		outcol = vec4(render_lights(tmp).xyz, 1);
}
