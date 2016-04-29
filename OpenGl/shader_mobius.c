/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader_mobius.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/24 13:42:58 by fnieto            #+#    #+#             */
/*   Updated: 2016/04/29 19:44:09 by jbyttner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** I tried deriving this as a cubic from
** y(x**2 + y**2 + z**2 - 1) - 2z(x**2 + y**2 + x) = 0
** from https://calculus7.org/2015/04/27/implicit-mobius-strip/
** --
** for a, b, c, d as the constants in a cubic
** --
** d is short for d.xyz. Operations are by component
** d.xy
** --
** a = (d**2 * d.y - 2 * d.xy**2 * d.z)
** b = (d**2 * p.y + 2 * (d.y * p * d - p.z * d.xy ** 2 - d.x * d.z - 2 * p.xy
** * d.xy))
** c = (d.y * p ** 2 + 2 * p * d * p.y - 2 * p.z * (d.x * 2 * p.xy * d.xy)
** - p.y - 2 * d.z * (p.xy ** 2 + p.x))
** d = (p.y * p ** 2 - 2 * p.z * (p.xy ** 2 + p.x) - p.y)
*/

/*
** Cubic as solved by
** http://www.math.vanderbilt.edu/~schectex/courses/cubic/
*/

s_res			mobius_dst(s_geo sp, s_cam cam, s_res prev)
{
	return (prev);
}
