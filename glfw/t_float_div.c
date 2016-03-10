/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_float_div.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 02:31:42 by fnieto            #+#    #+#             */
/*   Updated: 2016/03/10 18:53:46 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "cpugpu"

void		t_float_div(t_float *res, const t_float *a, const t_float *b)
{
	int		size[4];
	int		i;

	size[0] = sizeof(res) / sizeof(t_float);
	size[1] = sizeof(a) / sizeof(t_float);
	size[2] = sizeof(b) / sizeof(t_float);
	size[3] = MAX(size[1], size[2]);
	if (size[3] != 1 && size[3] < size[0])
		size[0] = size[3];
	i = -1;
	if (size[1] == 1 && size[2] == 1)
		while (++i < size[0])
			res[i] = a[0] / b[0];
	else if (size[1] == size[2])
		while (++i < size[0])
			res[i] = a[i] / b[i];
	else if (size[1] == 1)
		while (++i < size[0])
			res[i] = a[0] / b[i];
	else if (size[2] == 1)
		while (++i < size[0])
			res[i] = a[i] / b[0];
}
