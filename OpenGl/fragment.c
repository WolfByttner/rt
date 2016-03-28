/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fragment.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbyttner <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/26 21:44:17 by jbyttner          #+#    #+#             */
/*   Updated: 2016/03/28 19:27:30 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#version 330 core

# define	PI			3.1415926535

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
	vec4		e;
	s_mat		mat;
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

/*	uv = -(gl_FragCoord.xy / iResolution - 0.5) *
		iResolution.xy / float(iResolution.y) * iCameraZoom * PI / 2 -
		iCameraRotation * PI + PI / 2;
*/	cam.pos = iCameraPosition;
//	cam.ray = make_view_vector(uv);

	s_geo geo;
	geo.pos = vec3(5, 5, 10);
	geo.bounds = 1;

	s_res tmp;
	tmp.dst = -1;
	//tmp = sphere_dst(cam, geo, tmp);
	outcol = vec4(tmp.normal, 1);
}
