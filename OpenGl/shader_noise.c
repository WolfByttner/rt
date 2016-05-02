/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader_noise.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/02 20:10:40 by fnieto            #+#    #+#             */
/*   Updated: 2016/05/02 20:13:00 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

float		nrand(vec3 n)
{
	return (fract(sin(dot(n, VEC3(12.9898, 78.233, 34.1509))) * 43758.5453));
}

float		noise(vec3 p, int iter)
{
	int		i;
	float	tmp;

	i = -1;
	while (++i < iter)
	{
		tmp += nrand(floor((p += p * tmp) * i) / i);
	}
	return (tmp / iter);
}
