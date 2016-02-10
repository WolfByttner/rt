/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_shader.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/10 00:00:53 by fnieto            #+#    #+#             */
/*   Updated: 2016/02/10 02:30:03 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma OPENCL EXTENSION cl_khr_fp64 : enable

typedef	struct		s_geo
{
	size_t		type;
	double3		pos;
	double3		dim;
	double3		rot;
}					t_geo;

typedef	struct		s_cam
{
	double3		pos;
	double3		ray;
}					t_cam;

typedef	struct		s_ret
{
	double		t;
	double3		normal;
	double3		color;
}					t_ret;

static int			encode(double3 col)
{
	int		val;

	val = 0x10000 * (int)(clamp(col.x, 0., 1.) * 255.);
	val = val + 0x100 * (int)(clamp(col.y, 0., 1.) * 255.);
	val = val + 0x1 * (int)(clamp(col.z, 0., 1.) * 255.);
	return (val);
}

static t_ret		sphere_dst(t_cam cam, t_geo sp, t_ret prev)
{
	t_ret		ret;
	double3		rc;
	double3		v;

	rc = cam.pos-sp.pos;
	double c = dot(rc, rc) - (sp.dim.x*sp.dim.x);
	double b = dot(cam.ray, rc);
	double d = b*b - c;
	double t = -b - sqrt(fabs(d));
	double st = step(0.0, min(t,d));
	double m = mix(-1.0, t, st);
	ret.t = m;
	return (ret);
}

/*
 ** float st = step(0.0, min(t,d));
 ** return mix(-1.0, t, st);
 */

__kernel void		shader(
		__global const int* input,
		__global int* output,
		const size_t count,		//max des ids (ne pas toucher)
		const double2 res,		//resolution de l'ecran
		const double2 rot,		//rotation (fleches)
		const double3 pos,		//position (x: ad; y: ws, z: qe)
		const double4 mouse,	//position souris: xy, dernier click: zw
		const double zoom,		//zoom +- (pas pave numerique)
		const double time,		//temps
		const size_t frame,		//frame (nombe d'iterations passe, utile pour montecarlo)
		const size_t mode)		//incrementer avec barre d'espace: il faut le modulo.
{
	int		id;
	double2				coord;
	double2				uv;
	t_cam				cam;
	t_geo				sphere;

	id = get_global_id(0);
	if (((size_t)id) >= count)
		return ;
	coord = (double2)((id % (int)(res.x)), id / ((int)(res.x)));
	uv = ((coord / res) - 0.5) * 2 * (double2)(1, -1) * normalize(res) * zoom;
	cam.ray = normalize((double3)(uv, 1));
	cam.pos = pos + (double3)(0, 0, -3);
	sphere.pos = (double3)(0, 0, 0);
	sphere.dim.x = 1;
	t_ret tmp;
	tmp.t = -1;
	double t = sphere_dst(cam, sphere, tmp).t;
	output[id] = encode((double3)(1 / t));
}

