/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_shader.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/10 00:00:53 by fnieto            #+#    #+#             */
/*   Updated: 2016/02/10 18:49:47 by fnieto           ###   ########.fr       */
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
	t_geo		object;
}					t_ret;

__constant double	PI = 3.14159265358979323846;

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
	if ((ret.t > 0 && prev.t <= 0) || (ret.t > 0 && prev.t > 0 && ret.t < prev.t))
	{
		ret.object = sp;
		return (ret);
	}
	ret = prev;
	return (ret);
}

static t_ret		raytrace(t_cam cam, t_geo *geoms, size_t size)
{
	size_t		i;
	t_ret		tmp;

	tmp.t = -1;
	i = -1;
	while (++i < size)
		if (geoms[i].type == 0)
			tmp = sphere_dst(cam, geoms[i], tmp);
	return (tmp);
}

static double3		rotate_vec(double3 vec, double3 angls)
{
	double2		xrot;
	double2		yrot;
	double2		zrot;
	double3		tmp;

	tmp = vec;
	xrot.x = cos(angls.x);
	xrot.y = sin(angls.x);
	tmp = ((double3)(tmp.x * xrot.x - tmp.y * xrot.y,
		tmp.x * xrot.y + tmp.y * xrot.x, tmp.z));
	yrot.x = cos(angls.y);
	yrot.y = sin(angls.y);
	tmp = ((double3)(tmp.x * yrot.x + tmp.z * xrot.y, tmp.y,
		-tmp.x * xrot.y + tmp.z * xrot.x));
	zrot.x = cos(angls.z);
	zrot.y = sin(angls.z);
	tmp = ((double3)(tmp.x, tmp.y * zrot.x - tmp.z * zrot.y,
		tmp.y * zrot.y + tmp.z * zrot.x));
	return (tmp);
}

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
	t_geo				spheres[] = {{0, {0, 0, 0}, {1, 0, 0}, {0, 0, 0}}, {0, {0, 2, 2}, {1, 0, 0}, {0, 0, 0}}, {0, {0, 0, 10}, {7, 0, 0}, {0, 0, 0}}};

	id = get_global_id(0);
	if (((size_t)id) >= count)
		return ;
	coord = (double2)((id % (int)(res.x)), id / ((int)(res.x)));
	uv = -((coord / res) - 0.5) * (double2)(1, -1) * normalize(res) * zoom
		* PI / 2 - rot * PI / 50;
	cam.ray = normalize(rotate_vec((double3)(0, 0, 1), (double3)(uv.x, 0, uv.y)));
	cam.pos = pos.xzy * (double3)(10, 0.1, 10) + (double3)(0, 0, -3);
	t_ret tmp;
	tmp = raytrace(cam, spheres, sizeof(spheres) / sizeof(t_geo));
	output[id] = encode((double3)(1 / tmp.t));
//	output[id] = *(long*)&t;
}

