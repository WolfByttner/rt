/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mix_vec3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/08 15:35:49 by fnieto            #+#    #+#             */
/*   Updated: 2016/01/08 15:44:28 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fred_gl.h"

t_vec3		mix_vec3(t_vec3 a, t_vec3 b, t_vec3 alpha)
{
	a.x = MIX(a.x, b.x, alpha.x);
	a.y = MIX(a.y, b.y, alpha.y);
	a.z = MIX(a.z, b.z, alpha.z);
	return (a);
}

t_vec3		mix_vec3_1(t_vec3 a, t_vec3 b, t_float alpha)
{
	a.x = MIX(a.x, b.x, alpha);
	a.y = MIX(a.y, b.y, alpha);
	a.z = MIX(a.z, b.z, alpha);
	return (a);
}
