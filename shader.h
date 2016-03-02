/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbyttner <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 13:40:08 by jbyttner          #+#    #+#             */
/*   Updated: 2016/03/02 13:45:04 by jbyttner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHADER_H
# define SHADER_H

# ifdef CL_CONTEXT
# define CONSTANT __constant
# endif

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



CONSTANT double	PI = 3.14159265358979323846;

#endif
