/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mix_vec4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/08 15:35:49 by fnieto            #+#    #+#             */
/*   Updated: 2016/01/08 15:45:51 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fred_gl.h"

t_vec4		mix_vec4(t_vec4 a, t_vec4 b, t_vec4 alpha)
{
	a.x = MIX(a.x, b.x, alpha.x);
	a.y = MIX(a.y, b.y, alpha.y);
	a.z = MIX(a.z, b.z, alpha.z);
	a.w = MIX(a.w, b.w, alpha.w);
	return (a);
}

t_vec4		mix_vec4_1(t_vec4 a, t_vec4 b, t_float alpha)
{
	a.x = MIX(a.x, b.x, alpha);
	a.y = MIX(a.y, b.y, alpha);
	a.z = MIX(a.z, b.z, alpha);
	a.w = MIX(a.w, b.w, alpha);
	return (a);
}
