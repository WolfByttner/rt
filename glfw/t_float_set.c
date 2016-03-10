/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_float_set.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 02:31:42 by fnieto            #+#    #+#             */
/*   Updated: 2016/03/10 18:54:05 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "cpugpu"

void		t_float_set(t_float *res, const t_float *a)
{
	int		size[2];
	int		i;

	size[0] = sizeof(res) / sizeof(t_float);
	size[1] = sizeof(a) / sizeof(t_float);
	if (size[1] != 1)
		size[0] = MIN(size[0], size[1]);
	i = -1;
	if (size[1] == 1)
		while (++i < size[0])
			res[i] = a[0];
	else
		while (++i < size[0])
			res[i] = a[i];
}
