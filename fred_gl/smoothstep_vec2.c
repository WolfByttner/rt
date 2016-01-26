/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smoothstep_vec2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/08 15:35:49 by fnieto            #+#    #+#             */
/*   Updated: 2016/01/09 11:42:02 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fred_gl.h"

t_vec2		smoothstep_vec2(t_vec2 e0, t_vec2 e1, t_vec2 x)
{
	x.x = SMOOTHSTEP(e0.x, e1.x, x.x);
	x.y = SMOOTHSTEP(e0.y, e1.y, x.y);
	return (x);
}

t_vec2		smoothstep_vec2_1(t_float e0, t_float e1, t_vec2 x)
{
	x.x = SMOOTHSTEP(e0, e1, x.x);
	x.y = SMOOTHSTEP(e0, e1, x.y);
	return (x);
}
