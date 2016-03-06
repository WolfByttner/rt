/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shaderutil.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/07 16:51:34 by fnieto            #+#    #+#             */
/*   Updated: 2016/03/06 15:18:27 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int			upload_params(t_cl_instance *cl, t_cl_shader_info *info,
	size_t global)
{
	int		err;

	err = clSetKernelArg(cl->kernel, 0, sizeof(cl_mem), &(cl->input));
	err |= clSetKernelArg(cl->kernel, 1, sizeof(cl_mem), &(cl->output));
	err |= clSetKernelArg(cl->kernel, 2, sizeof(size_t), &global);
	err |= clSetKernelArg(cl->kernel, 3, sizeof(cl_double2), &(info->res));
	err |= clSetKernelArg(cl->kernel, 4, sizeof(cl_double2), &(info->rot));
	err |= clSetKernelArg(cl->kernel, 5, sizeof(cl_double3), &(info->pos));
	err |= clSetKernelArg(cl->kernel, 6, sizeof(cl_double4), &(info->mouse));
	err |= clSetKernelArg(cl->kernel, 7, sizeof(cl_double), &(info->zoom));
	err |= clSetKernelArg(cl->kernel, 8, sizeof(cl_double), &(info->time));
	err |= clSetKernelArg(cl->kernel, 9, sizeof(cl_uint), &(info->frame));
	err |= clSetKernelArg(cl->kernel, 10, sizeof(cl_uint), &(info->mode));
	if (err != CL_SUCCESS)
		return (-2);
	return (1);
}

t_cl_shader_info	*get_shader_info(void)
{
	static t_cl_shader_info	info;

	return (&info);
}

int					run_shader(t_buffer *buf)
{
	t_cl_shader_info	*info;
	t_cl_instance		*cl;
	int					err;
	size_t				global;
	cl_mem				swap;

	info = get_shader_info();
	cl = get_cl_instance();
	global = buf->w * buf->h;
	err = upload_params(cl, info, global);
	if (err < 1)
		return (err);
	err = clEnqueueNDRangeKernel(cl->commands, cl->kernel, 1, NULL,
		&global, NULL, 0, NULL, NULL);
	if (err)
		return (-4);
	clFinish(cl->commands);
	err = clEnqueueReadBuffer(cl->commands, cl->output, CL_TRUE, 0,
			sizeof(int) * global, (int*)buf->buf, 0, NULL, NULL);
	if (err != CL_SUCCESS)
		return (-5);
	swap = cl->input;
	cl->input = cl->output;
	cl->output = swap;
	return (1);
}
