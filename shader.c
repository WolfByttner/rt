/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/26 20:06:05 by fnieto            #+#    #+#             */
/*   Updated: 2016/01/26 20:11:18 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		shader(t_shader_info info)
{
	return (encode(info.i_frag_coord.x / info.i_resolution.x,
		info.i_frag_coord.y / info.i_resolution.y, FRACT(get_time())));
}
