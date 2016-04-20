/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fragment.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbyttner <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/26 21:44:17 by jbyttner          #+#    #+#             */
/*   Updated: 2016/04/20 23:36:29 by jbyttner         ###   ########.fr       */
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
# define	ELLIPSE		2
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

/*
**type: le type (pour le dispatch)
**pos: position
**bounds: la sphere englobant l'objet, <= 0 pour infini
**a, b, c, d: attributs supplementaires pouvant varier
**mat: le materiau de l'objet
*/
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

/*
**dst: la distance de la surface la plus proche, -1 si non existant
**normal: la normale de la surface
**cam: information du rayon
**mat: information du materiau
**color: la couleur finale de la surface
*/
struct			s_res
{
	float		dst;
	vec3		normal;
	s_cam		cam;
	s_mat		mat;
	vec4		color;
};

/*
**specular: la couleur speculaire: simulation de reflection de lumière forte
**
*/
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

/*
**s_mat[](s_mat(vec4(r, g, b, a), metallic, smoothness, vec2(transparency, refraction indice)))
**the definition of different materials, can be defined immediately in the object but putting it here is recommended
*/
s_mat ms[] = s_mat[](s_mat(vec4(1), 0.1, 0.8, vec2(0)),
		s_mat(vec4(1, 0, 0, 0), 0.1, 0.4, vec2(0)));

/*
**definition of the lights, to add light, increment LINUM and add an element to the array
*/
# define LINUM		2

	s_light lights[] = s_light[](
			s_light(vec4(1), vec3(cos(-10.0) * 10, 0, sin(-10.0) * 10)),
			s_light(vec4(0.5, 0.5, 1, 1), vec3(-cos(-10.0) * 10, 0, -sin(-10.0) * 10))
			);

/*
**definition of the objects, to add object, increment GEONUM and add an element to the array
*/
# define GEONUM		7

	s_geo geos[] = s_geo[](
			s_geo(SPHERE, vec3(0, 0, 0), 2, vec4(0), vec4(0), vec4(0), vec4(0), ms[0]),
			s_geo(SPHERE, vec3(-3, 0, 0), 1, vec4(0), vec4(0), vec4(0), vec4(0), ms[0]),
			s_geo(SPHERE, vec3(3, 0, 0), 1, vec4(0), vec4(0), vec4(0), vec4(0), ms[0]),
			s_geo(PLANE, vec3(-5, -2, -50), 0, vec4(0, 1, 0, 0), vec4(0), vec4(0), vec4(0), ms[0]),
			s_geo(SPHERE, vec3(0, 10, 0), 1, vec4(0), vec4(0), vec4(0), vec4(0), ms[1]),
			s_geo(CYLINDER, vec3(10, 10, 10), 0, vec4(0, 1, 0, 0), vec4(0, 3, 1, 0), vec4(0),
			vec4(0), ms[0]),
			s_geo(CONE, vec3(0, 5, -5), 0, vec4(0, 1, 0, 0.6), vec4(0, 3, 0, 0), vec4(0),
			vec4(0), ms[0]),
			s_geo(ELLIPSE, vec3(-12, 7, 0), 0, vec4(1, 1, 2, 4), vec4(2, 1, 0, 0), vec4(0), vec4(0),
			ms[1]));

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

/*
** TODO: Fill in these functions
** Indicate how you use the variables in s_geo.
*/

/*
** Ellipse
** a.xyz is the x y z 
** a.w is pointless // length along unit vector
** http://cudaopencl.blogspot.co.uk/2012/12/ellipsoids-finally-added-to-ray-tracing.html
*/

s_res		ellipse_dst(s_geo sp, s_cam cam, s_res prev)
/*
	Unsuccessful attempt 1
{
	float		a1, a2;
	float		a, b, c;
	float		r_sq;
	float		sq;
	vec3		rc;
	s_res		ret;

	rc = cam.pos - sp.pos;
	r_sq = pow(sp.b.x + sp.b.y, 2);
	a1 = 2 * sp.a.w * dot(cam.ray, sp.a.xyz);
	a2 = r_sq + 2 * sp.a.w * dot(rc, sp.a.xyz) - sp.a.w;
	r_sq *= 4;
	a = r_sq * dot(cam.ray, cam.ray) - pow(a1, 2);
	b = 2 * r_sq * dot(cam.ray, rc) - a1 * a2;
	c = r_sq * dot(rc, rc) - pow(a2, 2);
	sq = b * b - 4 * a * c;
	if (sq <= 0)
		return (prev);
	sq = sqrt(sq);
	ret.dst = (-b - sq) / (2 * a);
	if (ret.dst > 0 && (prev.dst <= 0 || ret.dst < prev.dst))
	{
		ret.mat = sp.mat;
		ret.cam = cam;
		ret.normal = vec3(1, 0, 0);
		return (ret);
	}
	return (prev);
}*/
{
	vec3	dir;
	vec3	centre;
	float	a, b, c;
	float	root;
	s_res	ret;

	centre = (cam.pos - sp.pos) / sp.a.xyz;
	dir = cam.ray / sp.a.xyz;
	a = dot(dir, dir);
	b = dot(dir, centre) * 2;
	c = dot(centre, centre) - 1;
	root = (pow(b, 2) - 4 * a * c);
	if (root <= 0)
		return (prev);
	root = sqrt(root);
	ret.dst = (-b - root) / (2 * a);
	if (ret.dst <= 0)
		ret.dst = (-b + root) / (2 * a);
	if (ret.dst > 0 && (prev.dst <= 0 || ret.dst < prev.dst))
	{
		ret.mat = sp.mat;
		ret.cam = cam;
		ret.normal = normalize(cam.pos + cam.ray * ret.dst - sp.pos);
		return (ret);
	}
	return (prev);
}

/*
** a.w is angle. a.xyz is normal (along the cone)
** http://hugi.scene.org/online/hugi24/coding%20graphics%20chris%20dragan%20raytracing%20shapes.htm
** b.x is mmin and b.y is m.max. b.z is radius at base (middle of cylinder)
** To construct a cone, set a.w to 0 and b.z to radius of cylinder
*/

s_res		cone_dst(s_geo sp, s_cam cam, s_res prev)
{
	float		a, b, c, m;
	float		root;
	float		rdot, pdot, opa2;
	vec3		pos;
	s_res		ret;

	pos = cam.pos - sp.pos;
	rdot = dot(cam.ray, sp.a.xyz);
	pdot = dot(pos, sp.a.xyz);
	opa2 = (1 + pow(sp.a.w, 2));
	a = dot(cam.ray, cam.ray) - opa2 * pow(rdot, 2);
	b = (dot(cam.ray, pos) - opa2 * rdot * pdot) * 2;
	c = dot(pos, pos) - opa2 * pow(pdot, 2) - pow(sp.b.z, 2);
	root = pow(b, 2) - 4 * a * c;
	if (root < 0)
		return (prev);
	root = sqrt(root);
	ret.dst = (-b - root) / (2 * a);
	if (ret.dst < 0)
		ret.dst = (-b + root) / (2 * a);
	m = rdot * ret.dst + pdot;
	if ((sp.b.x != 0 && sp.b.x > m) || (sp.b.y != 0 && m > sp.b.y))
	{
		ret.dst = (-b + root) / (2 * a);
		if (ret.dst < 0)
			return (prev);
		m = rdot * ret.dst + pdot;
		if ((sp.b.x == 0 || sp.b.x <= m) && (sp.b.y == 0 || m <= sp.b.y))
		{
			if (rdot == 0)
				return (prev);
			else
			{
				ret.dst = dot(pos, -sp.a.xyz) / rdot;
				if (ret.dst < 0)
					return (prev);
				ret.normal = -sp.a.xyz;
				ret.mat = sp.mat;
				ret.cam = cam;
				return (ret);
			}
		}
		else
			return (prev);
	}

	if (ret.dst > 0 && (prev.dst <= 0
		|| (prev.dst > 0 && ret.dst < prev.dst))
		&& (sp.b.x == 0 || sp.b.x <= m) 
		&& (sp.b.y == 0 || m <= sp.b.y))
	{
		ret.normal = normalize(cam.ray * ret.dst + pos - opa2 * sp.a.xyz * m);
		ret.mat = sp.mat;
		ret.cam = cam;
		return (ret);
	}
	return (prev);
}

s_res		cylinder_dst(s_geo sp, s_cam cam, s_res prev)
{
	return (cone_dst(sp, cam, prev));
}

s_res		box_dst(s_geo sp, s_cam cam, s_res prev)
{
	return (prev);
}

/*
** sp.a is the normal
** https://en.wikipedia.org/wiki/Line–plane_intersection
*/

s_res		plane_dst(s_geo sp, s_cam cam, s_res prev)
{
	s_res		ret;
	vec3		rc;
	float		tmp;

	ret.normal = -sp.a.xyz;
	tmp = dot(cam.ray, ret.normal);
	if ((tmp == 0))
		return (prev);
	rc = sp.pos.xyz - cam.pos;
	ret.dst = dot(rc, ret.normal) / tmp;
	if (ret.dst > 0 && (prev.dst <= 0 || (prev.dst > 0 && ret.dst < prev.dst)))
	{
		ret.mat = sp.mat;
		ret.cam = cam;
		return (ret);
	}
	return (prev);
}

s_res		klein_dst(s_geo sp, s_cam cam, s_res prev)
{
	return (prev);
}

s_res		mobius_dst(s_geo sp, s_cam cam, s_res prev)
{
	return (prev);
}

/*
** Dynamic dispatch
*/

s_res		obj_dst(s_geo obj, s_cam cam, s_res prev)
{
	if (obj.type == SPHERE)
		return (sphere_dst(obj, cam, prev));
	else if (obj.type == ELLIPSE)
		return (ellipse_dst(obj, cam, prev));
	else if (obj.type == CONE)
		return (cone_dst(obj, cam, prev));
	else if (obj.type == CYLINDER)
		return (cylinder_dst(obj, cam, prev));
	else if (obj.type == BOX)
		return (box_dst(obj, cam, prev));
	else if (obj.type == PLANE)
		return (plane_dst(obj, cam, prev));
	else if (obj.type == MOBIUS)
		return (mobius_dst(obj, cam, prev));
	else
		return (prev);
}

s_res		raytrace(s_cam cam)
{
	int		i;
	s_res	res;

	res.dst = -1;
	res.cam = cam;
	REP(8, res, obj_dst, geos, cam, res);
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
	ret.diffuse += abs(dot(res.normal, liret.cam.ray)) * light.color * li.z;
	ret.specular += pow(max(dot(reflect(liret.cam.ray, res.normal),
		-liret.cam.ray), 0), 5 / (1 - res.mat.smoothness)) * light.color * li.z;
	return (ret);
}

vec4		paint(s_res res, vec4 lastcol)
{
	int		i;
	s_liret	light;

	light.cam.pos = (res.dst - 0.001) * res.cam.ray + res.cam.pos;
	light.diffuse = vec4(0);
	light.specular = vec4(0);
	REP(2, light, iter_light, lights, light, res);
	return (max(mix(light.diffuse * res.mat.color + light.specular, lastcol,
		mix((1 - abs(dot(res.cam.ray, res.normal))) * res.mat.smoothness, 1,
		res.mat.metallic)), AMBIENT));
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

	specular = vec4(0);
	REP(2, specular, iter_spec, lights, specular, res);
	return (specular);
}

s_res		iterate(s_cam cam)
{
	//recursion stack
	s_res	iters[ITERATIONS];
	s_res	cur;
	int		i;
	s_cam	curcam;
	//recursion up
	curcam = cam;
	i = -1;
	while (++i < ITERATIONS)
	{
		cur = raytrace(curcam);
		iters[i] = cur;
		if (cur.dst == -1)
			break;
		//reflection of the camera
		curcam.pos = curcam.ray * cur.dst * 0.99 + curcam.pos;
		curcam.ray = reflect(curcam.ray, cur.normal);
	}
	//recursion down
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
	
	/*
	**rotation d'un cube et l'utilisation d'une face comme la camera ^
	**
	**code pour la pseudo recursion et le calcul de la couleur ici v
	*/
	
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
