/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fred_gl.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/08 14:05:50 by fnieto            #+#    #+#             */
/*   Updated: 2016/01/26 18:23:18 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRED_GL_H
# define FRED_GL_H

# include <string.h>
# include "libft.h"

# define ABS(a)					(a < 0 ? -a : a)
# define MIN(a, b)				(a < b ? a : b)
# define MAX(a, b)				(a > b ? a : b)
# define FLOOR(a)				((long)a)
# define CEIL(a)				(FRACT(a) != 0. ? FLOOR(a + 1) : FLOOR(a))
# define FRACT(a)				(a - FLOOR(a))
# define MOD(x, y)				(x - y * floor(x/y))
# define SIGN(a)				(a < 0 ? -1 : 1)
# define CLAMP(a, min, max)		(MIN(MAX(a, min), max))
# define MIX(a, b, alpha)		(a * (1 - alpha) + b * alpha)
# define SMSTUTIL(x)			(x * x * (3.0 - 2.0 * x))
# define SMOOTHSTEP(a, b, x)	(SMSTUTIL(CLAMP((x - a) / (b - a), 0.0, 1.0)))
# define STEP(edge, x)			(x >= edge)
# define LERP(a, b, x, max)		(MIX(a, b, x / max))
# define ROUND(a)				(FRACT(a) > 0.5 ? CEIL(a) : FLOOR(a))
# define OUT(a, min, max)		(a < min || a >= max)
# define SIZE(a, x)				((a + 1.) * (x / 2.))
# define T(a)					((t_type)a)

# define FUNCS			{0, &gl_lines, 0, 0}
# define FNC_SIZE		sizeof(FUNCS)

# define GL_ALL			0
# define GL_LEQUAL		-1
# define GL_GEQUAL		1

# define GL_POINTS		0
# define GL_LINES		1
# define GL_TRIANGLES	2
# define GL_QUADS		3

# define GL_MODELVIEW	0
# define GL_PROJECTION	1

# define GL_GET			0
# define GL_SET			1

typedef	double		t_float;

typedef	enum		e_interp
{
	NONE,
	FLOAT,
	VEC2,
	VEC3,
	VEC4
}					t_interp;

typedef	struct		s_vec2
{
	t_float	x;
	t_float	y;
}					t_vec2;

typedef	struct		s_vec3
{
	t_float	x;
	t_float	y;
	t_float	z;
}					t_vec3;

typedef	struct		s_vec4
{
	t_float	x;
	t_float	y;
	t_float	z;
	t_float	w;
}					t_vec4;

typedef	struct		s_mat4
{
	t_float	m00;
	t_float	m10;
	t_float	m20;
	t_float	m30;

	t_float	m01;
	t_float	m11;
	t_float	m21;
	t_float	m31;

	t_float	m02;
	t_float	m12;
	t_float	m22;
	t_float	m32;

	t_float	m03;
	t_float	m13;
	t_float	m23;
	t_float	m33;
}					t_mat4;

typedef	union		u_type
{
	short			s;
	unsigned short	us;
	int				i;
	unsigned int	ui;
	long			l;
	unsigned long	ul;
	float			f;
	double			d;
	char			c;
	unsigned char	uc;
	t_float			tf;
	void			*v;
	t_vec2			v2;
	t_vec3			v3;
	t_vec4			v4;
}					t_type;

typedef	struct		s_buffer
{
	size_t	w;
	size_t	h;
	size_t	type;
	void	*buf;
}					t_buffer;

typedef	struct		s_frame
{
	size_t			w;
	size_t			h;
	int				clear_undrawn;
	int				depth_func;
	t_buffer		*img;
	t_buffer		*depth;
	t_buffer		*change;
}					t_frame;

typedef	struct		s_attrib
{
	t_interp		interpolation;
	t_type			value;
}					t_attrib;

typedef	struct		s_vertex
{
	t_vec3			pos;
	t_attrib		attributes[8];
}					t_vertex;

typedef	struct		s_shader_info
{
	t_vec2			i_frag_coord;
	t_vec2			i_resolution;
	t_float			i_global_time;
	t_attrib		i_vertex_attribs[8];
}					t_shader_info;

typedef	int			(*t_shader)(t_shader_info shader_info);
typedef	int			(*t_draw_func)(int x, int y, int color);
typedef	void		(*t_vert_draw)(t_list*, t_shader, t_frame*);

typedef	struct		s_instance
{
	size_t			w;
	size_t			h;
	t_frame			*frame;
	t_draw_func		drawfn;
}					t_instance;

typedef	struct		s_gl_vert_i
{
	t_list			*lst;
	int				mode;
	t_attrib		attribs[8];
	t_shader		shader;
	t_frame			*frame;
}					t_gl_vert_i;

void				fred_gl_init(size_t w, size_t h, t_draw_func drawfn);

t_instance			*get_instance(void);

t_float				get_time(void);
void				set_time(t_float time);

t_vec2				vec2(t_float x, t_float y);
t_vec2				vec2_1(t_float x);

t_vec2				add_vec2(t_vec2 a, t_vec2 b);
t_vec2				sub_vec2(t_vec2 a, t_vec2 b);
t_vec2				mul_vec2(t_vec2 a, t_vec2 b);
t_vec2				div_vec2(t_vec2 a, t_vec2 b);
t_vec2				mix_vec2(t_vec2 a, t_vec2 b, t_vec2 alpha);
t_vec2				smoothstep_vec2(t_vec2 e0, t_vec2 e1, t_vec2 x);
t_vec2				lerp_vec2(t_vec2 a, t_vec2 b, t_vec2 x, t_vec2 max);
t_float				len_sq_vec2(t_vec2 a);
t_float				len_vec2(t_vec2 a);
t_float				dst_sq_vec2(t_vec2 a, t_vec2 b);
t_float				dst_vec2(t_vec2 a, t_vec2 b);

t_vec2				add_vec2_1(t_vec2 a, t_float b);
t_vec2				sub_vec2_1(t_vec2 a, t_float b);
t_vec2				mul_vec2_1(t_vec2 a, t_float b);
t_vec2				div_vec2_1(t_vec2 a, t_float b);
t_vec2				mix_vec2_1(t_vec2 a, t_vec2 b, t_float alpha);
t_vec2				smoothtep_vec2_1(t_float e0, t_float e1, t_vec2 x);
t_vec2				lerp_vec2_1(t_vec2 a, t_vec2 b, t_float x, t_float max);

t_vec3				vec3(t_float x, t_float y, t_float z);
t_vec3				vec3_1(t_float x);

t_vec3				add_vec3(t_vec3 a, t_vec3 b);
t_vec3				sub_vec3(t_vec3 a, t_vec3 b);
t_vec3				mul_vec3(t_vec3 a, t_vec3 b);
t_vec3				div_vec3(t_vec3 a, t_vec3 b);
t_vec3				mix_vec3(t_vec3 a, t_vec3 b, t_vec3 alpha);
t_vec3				smoothstep_vec3(t_vec3 e0, t_vec3 b, t_vec3 x);
t_vec3				lerp_vec3(t_vec3 a, t_vec3 b, t_vec3 x, t_vec3 max);
t_float				len_sq_vec3(t_vec3 a);
t_float				len_vec3(t_vec3 a);
t_float				dst_sq_vec3(t_vec3 a, t_vec3 b);
t_float				dst_vec3(t_vec3 a, t_vec3 b);

t_vec3				add_vec3_1(t_vec3 a, t_float b);
t_vec3				sub_vec3_1(t_vec3 a, t_float b);
t_vec3				mul_vec3_1(t_vec3 a, t_float b);
t_vec3				div_vec3_1(t_vec3 a, t_float b);
t_vec3				mix_vec3_1(t_vec3 a, t_vec3 b, t_float alpha);
t_vec3				smoothstep_vec3_1(t_float e0, t_float e1, t_vec3 x);
t_vec3				lerp_vec3_1(t_vec3 a, t_vec3 b, t_float x, t_float max);

t_vec4				vec4(t_float x, t_float y, t_float z, t_float w);
t_vec4				vec4_1(t_float x);

t_vec4				add_vec4(t_vec4 a, t_vec4 b);
t_vec4				sub_vec4(t_vec4 a, t_vec4 b);
t_vec4				mul_vec4(t_vec4 a, t_vec4 b);
t_vec4				div_vec4(t_vec4 a, t_vec4 b);
t_vec4				mix_vec4(t_vec4 a, t_vec4 b, t_vec4 alpha);
t_vec4				smoothstep_vec4(t_vec4 e0, t_vec4 e1, t_vec4 x);
t_vec4				lerp_vec4(t_vec4 a, t_vec4 b, t_vec4 x, t_vec4 max);
t_float				len_sq_vec4(t_vec4 a);
t_float				len_vec4(t_vec4 a);
t_float				dst_sq_vec4(t_vec4 a, t_vec4 b);
t_float				dst_vec4(t_vec4 a, t_vec4 b);

t_vec4				add_vec4_1(t_vec4 a, t_float b);
t_vec4				sub_vec4_1(t_vec4 a, t_float b);
t_vec4				mul_vec4_1(t_vec4 a, t_float b);
t_vec4				div_vec4_1(t_vec4 a, t_float b);
t_vec4				mix_vec4_1(t_vec4 a, t_vec4 b, t_float alpha);
t_vec4				smoothstep_vec4_1(t_float e0, t_float e1, t_vec4 x);
t_vec4				lerp_vec4_1(t_vec4 a, t_vec4 b, t_float x, t_float max);

t_mat4				mat4(t_vec4 r1, t_vec4 r2, t_vec4 r3, t_vec4 r4);
t_mat4				mat4_identity(void);
t_mat4				mat4_scale(t_vec3 scale);
t_mat4				mat4_translation(t_vec3 translation);
t_mat4				mat4_rotation(t_vec3 axis, t_float angle);

t_mat4				mul_mat4(t_mat4 a, t_mat4 b);
t_mat4				mul_mat4_1(t_mat4 a, t_float b);
t_vec4				mul_mat4_vec4(t_mat4 a, t_vec4 b);
t_vec3				mul_mat4_vec3(t_mat4 a, t_vec3 b);

t_mat4				cam_ortho(t_vec2 lr, t_vec2 tb, t_vec2 nf);

t_vertex			vertex(t_vec3 pos, t_attrib attribs[8]);
t_vertex			vert_lerp(t_vertex a, t_vertex b, t_float x, t_float max);
t_attrib			a_lerp(t_attrib a, t_attrib b, t_float x, t_float max);
t_attrib			attrib_null(void);

void				gl_pushmatrix(t_mat4 matrix);
void				gl_popmatrix(void);
int					gl_matrix_mode(int mat_mode);
t_vertex			gl_transform(t_vertex v);

void				gl_begin(int draw_mode, t_shader s, t_frame *f);
void				gl_param(t_type value, t_interp interpolation, int index);
void				gl_vertex(t_vec3 pos);
void				gl_end(void);
void				gl_draw_buf(t_list *buf, t_shader s, t_frame *f, int mode);

t_buffer			*buffer(size_t w, size_t h, size_t type);
t_type				buf_read(t_buffer *buf, size_t x, size_t y);
void				buf_write(t_buffer *buf, size_t x, size_t y, t_type val);
void				buffer_del(t_buffer **buf);

t_frame				*frame(size_t w, size_t h);
void				frame_put_pixel(t_frame *f, t_vertex v, t_shader shader);
void				frame_print(t_frame *f);
void				frame_del(t_frame **frame);

void				draw_line(t_vertex a, t_vertex b, t_shader s, t_frame *f);
void				gl_lines(t_list *v, t_shader s, t_frame *f);

int					encode(t_float r, t_float g, t_float b);
int					encode_vec3(t_vec3 color);
int					encode_vec4(t_vec4 color);

t_vec3				decode(int color);

int					f_to_i(float f);
float				i_to_f(int i);

#endif
