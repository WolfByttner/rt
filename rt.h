/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/26 18:42:50 by fnieto            #+#    #+#             */
/*   Updated: 2016/03/06 15:19:19 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include "libft.h"
# include "fred_gl.h"
# include <libc.h>
# include <OpenCL/opencl.h>
# define RT_DEVICE_TYPE CL_DEVICE_TYPE_CPU

/*
**comment to disable frame upload in input
*/

typedef	struct		s_cl_instance
{
	cl_device_id		device_id;
	cl_context			context;
	cl_command_queue	commands;
	cl_program			program;
	cl_kernel			kernel;
	cl_mem				input;
	cl_mem				output;
}					t_cl_instance;

typedef	struct		s_cl_shader_info
{
	t_vec2			res;
	t_vec3			pos;
	t_vec2			rot;
	t_vec4			mouse;
	double			zoom;
	double			time;
	size_t			mode;
	size_t			frame;
}					t_cl_shader_info;

typedef	struct		s_mlx
{
	void			*core;
	void			*window;
	void			*frame;
}					t_mlx;

typedef	struct		s_params
{
	t_vec2				res;
	int					ac;
	char				**av;
}					t_params;

t_cl_instance		*get_cl_instance(void);
int					print_cl_log(t_cl_instance *cl);
int					init_cl(cl_device_type type, const char *src, size_t bufsz);
void				deinit_cl(void);

t_cl_shader_info	*get_shader_info(void);
int					run_shader(t_buffer *buf);

#endif
