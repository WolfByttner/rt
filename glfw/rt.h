/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 21:45:13 by fnieto            #+#    #+#             */
/*   Updated: 2016/03/10 22:44:24 by fnieto           ###   ########.fr       */
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

typedef	float		t_float;

typedef	t_float		t_float1[1];
typedef	t_float		t_float2[2];
typedef	t_float		t_float3[3];
typedef	t_float		t_float4[4];

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
	t_float3	pos;
	t_float2	rot;
	size_t		frame;
}					t_spm;

typedef	struct		s_geo
{
	size_t		id;
	t_float		**data;
}					t_geo;

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

void				t_float_cross
(t_float3 r, const t_float3 a, const t_float3 b);

#endif
