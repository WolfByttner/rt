/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fragment.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/30 16:01:05 by fnieto            #+#    #+#             */
/*   Updated: 2016/05/02 20:24:08 by jbyttner         ###   ########.fr       */
/*   Updated: 2016/05/02 18:44:08 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Include in GPU code
*/

#ifndef FRAGMENT_H
# define FRAGMENT_H

# pragma optionNV(fastmath on)
# pragma optionNV(fastprecision on)
# pragma optionNV(ifcvt all)
# pragma optionNV(inline all)
# pragma optionNV(strict off)
# pragma optionNV(unroll all)

# define PI 3.1415926535897932384626433832795

# define IGNORE		0
# define SPHERE		1
# define ELLIPSE	2
# define CONE		3
# define CYLINDER	4
# define BOX		5
# define PLANE		6


# define KLEIN		11
# define MOBIUS		12
# define HEART		13

# define FLAT		21
# define CHECKBOARD	22
# define BUMP		23
# define WAVE		24
# define RTILES		25
# define RAND		26
# define PERLIN		27

# define ITERATIONS	4
# define AMBIENT		(vec4(0.06, 0.04, 0.08, 0))

# define REP_1(r, f, a, b, c) (r = f( a [0], b, c));
# define REP_2(r, f, a, b, c)	REP_1(r, f, a, b, c)(r = f(a[1], b, c));
# define REP_3(r, f, a, b, c)	REP_2(r, f, a, b, c)(r = f(a[2], b, c));
# define REP_4(r, f, a, b, c)	REP_3(r, f, a, b, c)(r = f(a[3], b, c));
# define REP_5(r, f, a, b, c)	REP_4(r, f, a, b, c)(r = f(a[4], b, c));
# define REP_6(r, f, a, b, c)	REP_5(r, f, a, b, c)(r = f(a[5], b, c));
# define REP_7(r, f, a, b, c)	REP_6(r, f, a, b, c)(r = f(a[6], b, c));
# define REP_8(r, f, a, b, c)	REP_7(r, f, a, b, c)(r = f(a[7], b, c));
# define REP_9(r, f, a, b, c)	REP_8(r, f, a, b, c)(r = f(a[8], b, c));
# define REP_10(r, f, a, b, c)	REP_9(r, f, a, b, c)(r = f(a[9], b, c));
# define REP_11(r, f, a, b, c)	REP_10(r, f, a, b, c)(r = f(a[10], b, c));
# define REP_12(r, f, a, b, c)	REP_11(r, f, a, b, c)(r = f(a[11], b, c));
# define REP_13(r, f, a, b, c)	REP_12(r, f, a, b, c)(r = f(a[12], b, c));
# define REP_14(r, f, a, b, c)	REP_13(r, f, a, b, c)(r = f(a[13], b, c));
# define REP_15(r, f, a, b, c)	REP_14(r, f, a, b, c)(r = f(a[14], b, c));
# define REP_16(r, f, a, b, c)	REP_15(r, f, a, b, c)(r = f(a[15], b, c));
# define REP_17(r, f, a, b, c)	REP_16(r, f, a, b, c)(r = f(a[16], b, c));
# define REP_18(r, f, a, b, c)	REP_17(r, f, a, b, c)(r = f(a[17], b, c));
# define REP_19(r, f, a, b, c)	REP_18(r, f, a, b, c)(r = f(a[18], b, c));
# define REP_20(r, f, a, b, c)	REP_19(r, f, a, b, c)(r = f(a[19], b, c));
# define REP_21(r, f, a, b, c)	REP_20(r, f, a, b, c)(r = f(a[20], b, c));
# define REP_22(r, f, a, b, c)	REP_21(r, f, a, b, c)(r = f(a[21], b, c));
# define REP_23(r, f, a, b, c)	REP_22(r, f, a, b, c)(r = f(a[22], b, c));
# define REP_24(r, f, a, b, c)	REP_23(r, f, a, b, c)(r = f(a[23], b, c));
# define REP_25(r, f, a, b, c)	REP_24(r, f, a, b, c)(r = f(a[24], b, c));
# define REP_26(r, f, a, b, c)	REP_25(r, f, a, b, c)(r = f(a[25], b, c));
# define REP_27(r, f, a, b, c)	REP_26(r, f, a, b, c)(r = f(a[26], b, c));
# define REP_28(r, f, a, b, c)	REP_27(r, f, a, b, c)(r = f(a[27], b, c));
# define REP_29(r, f, a, b, c)	REP_28(r, f, a, b, c)(r = f(a[28], b, c));
# define REP_30(r, f, a, b, c)	REP_29(r, f, a, b, c)(r = f(a[29], b, c));
# define REP_31(r, f, a, b, c)	REP_30(r, f, a, b, c)(r = f(a[30], b, c));

# define REP(n, r, f, a, b, c)	REP_##n(r, f, a, b, c)

# define VEC2					vec2
# define VEC3					vec3
# define VEC4					vec4

# define MAT3					mat3
# define FLOAT					float
# define S_GEO					s_geo
# define S_TEXMOD				s_texmod

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
	int			m_id;
	vec4		m_param;
	vec2		m_prop;
	vec4		m_color;
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
*/
struct			s_liret
{
	vec4		specular;
	vec4		diffuse;
	s_cam		cam;
};

struct			s_texmod
{
	vec4		color;
	vec3		normal;
	float		smoothness;
	float		metallic;
};

float			solve_quadratic(float a, float b, float c);
s_res			iterate(s_cam cam);
s_res			box_dst(s_geo sp, s_cam cam, s_res prev);
s_res			cone_dst(s_geo sp, s_cam cam, s_res prev);
s_res			cylinder_dst(s_geo sp, s_cam cam, s_res prev);
s_res			ellipse_dst(s_geo sp, s_cam cam, s_res prev);
s_res			klein_dst(s_geo sp, s_cam cam, s_res prev);
s_res			mobius_dst(s_geo sp, s_cam cam, s_res prev);
s_res			plane_dst(s_geo sp, s_cam cam, s_res prev);
s_res			sphere_dst(s_geo sp, s_cam cam, s_res prev);
s_res			heart_dst(s_geo sp, s_cam cam, s_res prev);
s_res			iterate(s_cam cam);
vec4			paint(s_res res, vec4 lastcol);
s_res			raytrace(s_cam cam);

#endif
