/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader_quadratic.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbyttner <jbyttner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/25 17:26:26 by jbyttner          #+#    #+#             */
/*   Updated: 2016/04/30 16:44:05 by jbyttner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATIONS
# error "Iterations not defined"
#endif
#if ITERATIONS > 30
# error "Too many iterations"
#elif ITERATIONS < 1
# error "Too few iterations"
#endif
#ifndef GEONUM
# error "Geonum not defined"
#endif
#if GEONUM > 30
# error "Too many objects"
#elif GEONUM < 1
# error "Too few objects"
#endif
#ifndef LINUM
# error "Linum not defined"
#endif
#if LINUM > 30
# error "Too many lights"
#elif LINUM < 1
# error "Too few lights"
#endif

/*
** Gives lowest non-negative t
** Returns -1 on failure
*/

float		solve_quadratic(float a, float b, float c)
{
	float	root;
	float	t1;
	float	t2;

	root = (pow(b, 2) - 4 * a * c);
	if (root < 0)
		return (-1);
	root = sqrt(root);
	t1 = (-b - root) / (2 * a);
	t2 = (-b + root) / (2 * a);
	if (t1 >= 0 && t2 >= 0)
		return (min(t1, t2));
	if (t1 >= 0)
		return (t1);
	if (t2 >= 0)
		return (t2);
	return (-1);
}
