/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mix_vec2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/08 15:35:49 by fnieto            #+#    #+#             */
/*   Updated: 2016/01/08 15:42:21 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fred_gl.h"

t_vec2		mix_vec2(t_vec2 a, t_vec2 b, t_vec2 alpha)
{
	a.x = MIX(a.x, b.x, alpha.x);
	a.y = MIX(a.y, b.y, alpha.y);
	return (a);
}

t_vec2		mix_vec2_1(t_vec2 a, t_vec2 b, t_float alpha)
{
	a.x = MIX(a.x, b.x, alpha);
	a.y = MIX(a.y, b.y, alpha);
	return (a);
}
