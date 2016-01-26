/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   len_vec4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/11 17:27:51 by fnieto            #+#    #+#             */
/*   Updated: 2016/01/18 15:49:50 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fred_gl.h"
#include <math.h>

t_float		len_sq_vec4(t_vec4 a)
{
	return (a.x * a.x + a.y * a.y + a.z * a.z + a.w * a.w);
}

t_float		len_vec4(t_vec4 a)
{
	return (sqrt(len_sq_vec4(a)));
}

t_float		dst_sq_vec4(t_vec4 a, t_vec4 b)
{
	return (len_sq_vec4(sub_vec4(b, a)));
}

t_float		dst_vec4(t_vec4 a, t_vec4 b)
{
	return (sqrt(dst_sq_vec4(a, b)));
}
