/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lerp_vec2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/08 15:35:49 by fnieto            #+#    #+#             */
/*   Updated: 2016/01/09 11:32:01 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fred_gl.h"

t_vec2		lerp_vec2(t_vec2 a, t_vec2 b, t_vec2 x, t_vec2 max)
{
	a.x = LERP(a.x, b.x, x.x, max.x);
	a.y = LERP(a.y, b.y, x.y, max.y);
	return (a);
}

t_vec2		lerp_vec2_1(t_vec2 a, t_vec2 b, t_float x, t_float max)
{
	a.x = LERP(a.x, b.x, x, max);
	a.y = LERP(a.y, b.y, x, max);
	return (a);
}
