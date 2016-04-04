/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fragment.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbyttner <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/26 21:44:17 by jbyttner          #+#    #+#             */
/*   Updated: 2016/04/04 19:17:59 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#version 330 core

#pragma optionNV(fastmath on)
#pragma optionNV(fastprecision on)
#pragma optionNV(ifcvt all)
#pragma optionNV(inline all)
#pragma optionNV(strict off)
#pragma optionNV(unroll all)

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

# define	ITERATIONS	4
# define	AMBIENT		(vec4(0.06, 0.04, 0.08, 0))

# define	REP_1(r, f, a, b, c)	(r = f( a [0], b, c));
# define	REP_2(r, f, a, b, c)	REP_1(r, f, a, b, c)(r = f(a[1], b, c));
# define	REP_3(r, f, a, b, c)	REP_2(r, f, a, b, c)(r = f(a[2], b, c));
# define	REP_4(r, f, a, b, c)	REP_3(r, f, a, b, c)(r = f(a[3], b, c));
# define	REP_5(r, f, a, b, c)	REP_4(r, f, a, b, c)(r = f(a[4], b, c));
# define	REP_6(r, f, a, b, c)	REP_5(r, f, a, b, c)(r = f(a[5], b, c));
# define	REP_7(r, f, a, b, c)	REP_6(r, f, a, b, c)(r = f(a[6], b, c));
# define	REP_8(r, f, a, b, c)	REP_7(r, f, a, b, c)(r = f(a[7], b, c));
# define	REP_9(r, f, a, b, c)	REP_8(r, f, a, b, c)(r = f(a[8], b, c));
# define	REP_10(r, f, a, b, c)	REP_9(r, f, a, b, c)(r = f(a[9], b, c));
# define	REP_11(r, f, a, b, c)	REP_10(r, f, a, b, c)(r = f(a[10], b, c));
# define	REP_12(r, f, a, b, c)	REP_11(r, f, a, b, c)(r = f(a[11], b, c));
# define	REP_13(r, f, a, b, c)	REP_12(r, f, a, b, c)(r = f(a[12], b, c));
# define	REP_14(r, f, a, b, c)	REP_13(r, f, a, b, c)(r = f(a[13], b, c));
# define	REP_15(r, f, a, b, c)	REP_14(r, f, a, b, c)(r = f(a[14], b, c));
# define	REP_16(r, f, a, b, c)	REP_15(r, f, a, b, c)(r = f(a[15], b, c));
# define	REP_17(r, f, a, b, c)	REP_16(r, f, a, b, c)(r = f(a[16], b, c));
# define	REP_18(r, f, a, b, c)	REP_17(r, f, a, b, c)(r = f(a[17], b, c));
# define	REP_19(r, f, a, b, c)	REP_18(r, f, a, b, c)(r = f(a[18], b, c));
# define	REP_20(r, f, a, b, c)	REP_19(r, f, a, b, c)(r = f(a[19], b, c));
# define	REP_21(r, f, a, b, c)	REP_20(r, f, a, b, c)(r = f(a[20], b, c));
# define	REP_22(r, f, a, b, c)	REP_21(r, f, a, b, c)(r = f(a[21], b, c));
# define	REP_23(r, f, a, b, c)	REP_22(r, f, a, b, c)(r = f(a[22], b, c));
# define	REP_24(r, f, a, b, c)	REP_23(r, f, a, b, c)(r = f(a[23], b, c));
# define	REP_25(r, f, a, b, c)	REP_24(r, f, a, b, c)(r = f(a[24], b, c));
# define	REP_26(r, f, a, b, c)	REP_25(r, f, a, b, c)(r = f(a[25], b, c));
# define	REP_27(r, f, a, b, c)	REP_26(r, f, a, b, c)(r = f(a[26], b, c));
# define	REP_28(r, f, a, b, c)	REP_27(r, f, a, b, c)(r = f(a[27], b, c));
# define	REP_29(r, f, a, b, c)	REP_28(r, f, a, b, c)(r = f(a[28], b, c));
# define	REP_30(r, f, a, b, c)	REP_29(r, f, a, b, c)(r = f(a[29], b, c));
# define	REP_31(r, f, a, b, c)	REP_30(r, f, a, b, c)(r = f(a[30], b, c));

# define	REP(n, r, f, a, b, c)	REP_##n(r, f, a, b, c)

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
	vec4		color;
};

struct			s_liret
{
	vec4		specular;
	vec4		diffuse;
	s_cam		cam;
};

uniform ivec2 iResolution;
uniform vec3 iCameraPosition = vec3(0, 0, 0);
uniform vec2 iCameraRotation = vec2(0, 0);
uniform float iCameraZoom = 1;
uniform float iGlobalTime = 0;

layout (location = 0) out vec4 outcol;

s_mat ms[] = s_mat[](s_mat(vec4(1), 0.1, 0.8, vec2(0)));

# define LINUM		2

	s_light lights[] = s_light[](
			s_light(vec4(1), vec3(cos(-10) * 10, 0, sin(-10) * 10)),
			s_light(vec4(0.5, 0.5, 1, 1), vec3(-cos(-10) * 10, 0, -sin(-10) * 10))
			);

# define GEONUM		3

	s_geo geos[] = s_geo[](
			s_geo(SPHERE, vec3(0, 0, 0), 2, vec4(0), vec4(0), vec4(0), vec4(0), ms[0]),
			s_geo(SPHERE, vec3(-3, 0, 0), 1, vec4(0), vec4(0), vec4(0), vec4(0), ms[0]),
			s_geo(SPHERE, vec3(3, 0, 0), 1, vec4(0), vec4(0), vec4(0), vec4(0), ms[0]));

vec3		sphere_norm(s_cam cam, s_res ret, s_geo object)
{
	return (-normalize(object.pos - (cam.pos + cam.ray * ret.dst)));
}

s_res		sphere_dst(s_geo sp, s_cam cam, s_res prev)
{
	s_res		ret;
	vec3		rc;
	float		b, d, t, l2;

	rc = cam.pos - sp.pos;
	l2 = dot(rc, rc);
	b = dot(cam.ray, rc);
	d = pow(b, 2) - l2 + pow(sp.bounds, 2);
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

s_res		obj_dst(s_geo obj, s_cam cam, s_res prev)
{
	if (obj.type == SPHERE)
		return (sphere_dst(obj, cam, prev));
	else
		return (prev);
}

s_res		raytrace(s_cam cam)
{
	int		i;
	s_res	res;

	res.dst = -1;
	res.cam = cam;
	REP(GEONUM, res, obj_dst, geos, cam, res);
	return (res);
}

s_res		iter_scene( s_res res)
{
	return (res);
}

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
	ret.diffuse += max(dot(res.normal, liret.cam.ray), 0) * light.color * li.z;
	ret.specular += pow(max(dot(reflect(liret.cam.ray, res.normal),
		-liret.cam.ray), 0), 5 / (1 - res.mat.smoothness)) * light.color * li.z;
	return (ret);
}

vec4		paint(s_res res, vec4 lastcol)
{
	int		i;
	s_liret	light;

	light.cam.pos = (res.dst - 0.001) * res.cam.ray + res.cam.pos;
	REP(LINUM, light, iter_light, lights, light, res);
	return (max(mix(light.diffuse * res.mat.color, lastcol *
		res.mat.smoothness, res.mat.metallic) + light.specular *
		res.mat.smoothness, AMBIENT));
}

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

vec4		render_lights(s_res res)
{
	vec4	specular;

	REP(LINUM, specular, iter_spec, lights, specular, res);
	return (specular);
}

s_res		iterate(s_cam cam)
{
	s_res	iters[ITERATIONS];
	s_res	cur;
	int		i;
	s_cam	curcam;

	curcam = cam;
	i = -1;
	while (++i < ITERATIONS)
	{
		cur = raytrace(curcam);
		iters[i] = cur;
		if (cur.dst == -1)
			break;
		curcam.pos = curcam.ray * cur.dst * 0.99 + curcam.pos;
		curcam.ray = reflect(curcam.ray, cur.normal);
	}
	--i;
	iters[i].color = paint(iters[i], vec4(0));
	while (i-- > 0)
		iters[i].color = paint(iters[i], iters[i + 1].color);
	return (iters[0]);
}

void		main()
{
	s_cam	cam;
	vec2	uv;
	vec2	fov;
	vec4	sins;

	uv = gl_FragCoord.xy / iResolution;
	vec2 camrot = vec2(iCameraRotation.x,
		clamp(iCameraRotation.y, -PI / 2, PI / 2));
	sins = vec4(sin(camrot.x), cos(camrot.x), sin(camrot.y), cos(camrot.y));
	cam.pos = iCameraPosition;
	cam.pos.z -= 10;
	mat3 transform = (
		mat3(1, 0, 0, 0, sins.w, -sins.z, 0, sins.z, sins.w)
		* mat3(sins.y, 0, sins.x, 0, 1, 0, -sins.x, 0, sins.y)
		);
	vec2 ratio = iResolution.xy / float(iResolution.y);
	vec3 a = vec3(-1, -1, 1) * transform * vec3(iCameraZoom * ratio, 1);
	vec3 b = vec3(1, -1, 1) * transform * vec3(iCameraZoom * ratio, 1);
	vec3 c = vec3(-1, 1, 1) * transform * vec3(iCameraZoom * ratio, 1);
	vec3 d = vec3(1, 1, 1) * transform * vec3(iCameraZoom * ratio, 1);
	vec3 s = mix(a, b, uv.x);
	vec3 t = mix(c, d, uv.x);
	cam.ray = normalize(mix(s, t, uv.y));
	s_res tmp = iterate(cam);
	if (tmp.dst != -1)
	{
		vec4 col = tmp.color;
		tmp.cam = cam;
		col += render_lights(tmp);
		outcol = vec4(col.xyz, 1);
	}
	else
		outcol = vec4(render_lights(tmp).xyz, 1);
}
