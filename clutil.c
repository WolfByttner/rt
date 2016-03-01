/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clutil.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/06 20:30:28 by fnieto            #+#    #+#             */
/*   Updated: 2016/03/01 23:07:42 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int		init_buffers(t_cl_instance *cl, size_t bufsz)
{
	cl->output = clCreateBuffer(cl->context, CL_MEM_READ_WRITE,
		sizeof(int) * bufsz, NULL, NULL);
	cl->input = clCreateBuffer(cl->context, CL_MEM_READ_WRITE,
		sizeof(int) * bufsz, NULL, NULL);
	if (!cl->input || !cl->output)
		return (-7);
	return (0);
}

t_cl_instance	*get_cl_instance(void)
{
	static t_cl_instance	instance;

	return (&instance);
}

int				print_cl_log(t_cl_instance *cl)
{
	size_t			len;
	char			buffer[131072];

	clGetProgramBuildInfo(cl->program, cl->device_id, CL_PROGRAM_BUILD_LOG,
			sizeof(buffer), buffer, &len);
	ft_putendl(buffer);
	ft_putnbr(len);
	ft_putendl("");
	return (-4);
}

int				init_cl(cl_device_type type, const char *src, size_t bufsz)
{
	t_cl_instance	*cl;
	int				err;

	cl = get_cl_instance();
	err = clGetDeviceIDs(NULL, type, 1, &(cl->device_id), NULL);
	if (err != CL_SUCCESS)
		return (0);
	cl->context = clCreateContext(0, 1, &(cl->device_id), NULL, NULL, &err);
	if (!cl->context)
		return (-1);
	cl->commands = clCreateCommandQueue(cl->context, cl->device_id, 0, &err);
	cl->program = clCreateProgramWithSource(cl->context, 1, &src, NULL, &err);
	if (!cl->program || !cl->commands)
		return ((!cl->commands) ? (-2) : (-3));
	err = clBuildProgram(cl->program, 0, NULL, "-I .", NULL, NULL);
	if (err != CL_SUCCESS)
		return (print_cl_log(cl));
	print_cl_log(cl);
	cl->kernel = clCreateKernel(cl->program, "shader", &err);
	if (!cl->kernel || err != CL_SUCCESS)
		return (-5 - (err != CL_SUCCESS));
	err = init_buffers(cl, bufsz);
	if (err)
		return (err);
	return (1);
}

void			deinit_cl(void)
{
	t_cl_instance *cl;

	cl = get_cl_instance();
	clReleaseMemObject(cl->output);
	clReleaseMemObject(cl->input);
	clReleaseProgram(cl->program);
	clReleaseKernel(cl->kernel);
	clReleaseCommandQueue(cl->commands);
	clReleaseContext(cl->context);
}
