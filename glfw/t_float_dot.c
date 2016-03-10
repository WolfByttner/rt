/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_float_dot.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 02:31:42 by fnieto            #+#    #+#             */
/*   Updated: 2016/03/10 18:53:51 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "cpugpu"

void		t_float_dot(t_float *res, const t_float *a, const t_float *b)
{
	int		size;
	int		i;
	t_float	tmp;

	tmp = 0;
	size = MIN(sizeof(a), sizeof(b)) / sizeof(t_float);
	i = -1;
	while (++i < size)
	{
		tmp += a[i] * b[i];
	}
	*res = tmp;
}
