/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   len_vec2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/11 17:27:51 by fnieto            #+#    #+#             */
/*   Updated: 2016/01/18 15:50:03 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fred_gl.h"
#include <math.h>

t_float		len_sq_vec2(t_vec2 a)
{
	return (a.x * a.x + a.y * a.y);
}

t_float		len_vec2(t_vec2 a)
{
	return (sqrt(len_sq_vec2(a)));
}

t_float		dst_sq_vec2(t_vec2 a, t_vec2 b)
{
	return (len_sq_vec2(sub_vec2(b, a)));
}

t_float		dst_vec2(t_vec2 a, t_vec2 b)
{
	return (sqrt(dst_sq_vec2(a, b)));
}
