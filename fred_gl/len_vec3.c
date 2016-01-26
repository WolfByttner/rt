/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   len_vec3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/11 17:27:51 by fnieto            #+#    #+#             */
/*   Updated: 2016/01/18 15:49:56 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fred_gl.h"
#include <math.h>

t_float		len_sq_vec3(t_vec3 a)
{
	return (a.x * a.x + a.y * a.y + a.z * a.z);
}

t_float		len_vec3(t_vec3 a)
{
	return (sqrt(len_sq_vec3(a)));
}

t_float		dst_sq_vec3(t_vec3 a, t_vec3 b)
{
	return (len_sq_vec3(sub_vec3(b, a)));
}

t_float		dst_vec3(t_vec3 a, t_vec3 b)
{
	return (sqrt(dst_sq_vec3(a, b)));
}
