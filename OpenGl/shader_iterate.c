/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader_iterate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/24 13:26:20 by fnieto            #+#    #+#             */
/*   Updated: 2016/04/24 13:29:57 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**recusrsion simulation for tracing the path forwards, and coloring backwards
*/

s_res		iterate(s_cam cam)
{
	s_res	iters[ITERATIONS];
	s_res	cur;
	int		i;
	s_cam	curcam;

	curcam = cam;
	i = -1;
	while (++i < ITERATIONS)
	{
		cur = raytrace(curcam);
		iters[i] = cur;
		if (cur.dst == -1)
			break ;
		curcam.pos = curcam.ray * cur.dst * 0.99 + curcam.pos;
		curcam.ray = reflect(curcam.ray, cur.normal);
	}
	--i;
	iters[i].color = paint(iters[i], vec4(0));
	while (i-- > 0)
		iters[i].color = paint(iters[i], iters[i + 1].color);
	return (iters[0]);
}
