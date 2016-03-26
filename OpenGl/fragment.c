/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fragment.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbyttner <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/26 21:44:17 by jbyttner          #+#    #+#             */
/*   Updated: 2016/03/26 21:59:48 by jbyttner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#version 330 core

typedef struct	s_ray
{
	vec4		ray;
	vec4		material;
}				t_ray;

uniform ivec2 iResolution;

layout (location = 0) out vec4 outcol;

t_ray	circle_intersect()
{

}

void	main()
{
	vec2 uv = gl_FragCoord.xy / iResolution;
	outcol = vec4(uv, 0, 1);
	if (length (uv) > 1)
		outcol.xy = vec2(0);
}
