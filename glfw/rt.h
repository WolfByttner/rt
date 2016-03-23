/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 21:45:13 by fnieto            #+#    #+#             */
/*   Updated: 2016/03/11 00:36:01 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include <string.h>

# define P_NAME							"R.T. (Ronald Trump)"
# define CUDA_CALL(n, x, y, ...)		n<<<x, y>>>(__VA_ARGS__)
# define GEN_GRID(x, y)					dim3 grid(x, y)

# define MAX(a, b)						((a > b) ? (a) : (b))
# define MIN(a, b)						((a < b) ? (a) : (b))

typedef	enum		e_g_types
{
	T_FLOAT,
	VEC2,
	VEC3,
	VEC4
}					t_g_types;

# define G_T_FLOAT						t_float: T_FLOAT
# define G_VEC2							t_vec2: VEC2
# define G_VEC3							t_vec3: VEC3
# define G_VEC4							t_vec4: VEC4
# define G1								G_T_FLOAT, G_VEC2
# define G2								G_VEC3, G_VEC4
# define GEN(x)							_Generic((x), G1, G2)
# define G(x)							(gen(GEN(x), (void*)&(x)))

typedef	struct		s_gen
{
	t_g_types	type;
	void		*var;
}					t_gen;

typedef	float		t_float;

typedef	struct		s_vec2
{
	t_float		x;
	t_float		y;
}					t_vec2;

typedef	struct		s_vec3
{
	t_float		x;
	t_float		y;
	t_float		z;
}					t_vec3;

typedef	struct		s_vec4
{
	t_float		x;
	t_float		y;
	t_float		z;
	t_float		w;
}					t_vec4;

typedef	struct		s_params
{
	int		res[2];
}					t_params;

typedef	struct		s_smem
{
	void	*host;
	void	*device;
	size_t	size;
}					t_smem;

typedef	struct		s_rt
{
	t_params	*pms;
	t_smem		*map;
	t_smem		*frame;
	t_smem		*result;
}					t_rt;

typedef	struct		s_spm
{
	t_float		zoom;
	t_vec3	pos;
	t_vec2	rot;
	size_t		frame;
}					t_spm;

typedef	struct		s_geo
{
	size_t		id;
	t_float		**data;
}					t_geo;

t_gen				gen(t_g_types type, void *ptr);

void				test_kernel(int *res, int frame);

int					ft_atoi(const char *str);

void				err(char *str);
void				cudaerr(cudaError_t error, char *file, int line);

t_smem				*malloc_smem(size_t size);
void				free_smem(t_smem **mem);
void				sync_host(t_smem *mem);
void				sync_device(t_smem *mem);

void				t_float_set(t_float *r, const t_float *a);
void				t_float_setv(t_float *r, const t_float a);
void				t_float_add(t_float *r, const t_float *a, const t_float *b);
void				t_float_sub(t_float *r, const t_float *a, const t_float *b);
void				t_float_mul(t_float *r, const t_float *a, const t_float *b);
void				t_float_div(t_float *r, const t_float *a, const t_float *b);
void				t_float_dot(t_float *r, const t_float *a, const t_float *b);

void				t_float_cross(t_vec3 r, const t_vec3 a, const t_vec3 b);

#endif
