/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_kernel.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 21:37:34 by fnieto            #+#    #+#             */
/*   Updated: 2016/03/10 21:38:23 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "gpu"

void			test_kernel(int *res, int frame)
{
	int		pos[3];

	pos[0] = blockIdx.x;
	pos[1] = blockIdx.y;
	pos[2] = pos[0] + pos[1] * gridDim.x;
	res[pos[2]] = frame * 0x100 + 0xFF;
}
