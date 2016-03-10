/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_float_reflect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 02:31:42 by fnieto            #+#    #+#             */
/*   Updated: 2016/03/10 18:53:59 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "cpugpu"

void		t_float_reflect(t_float *res, const t_float *v, const t_float *n)
{
	t_float1	v1;
	t_float4	v2;

	t_float_dot(v1, n, v);
	v1[0] *= 2;
	t_float_mul(v2, n, v1);
	t_float_sub(res, v, v2);
}
