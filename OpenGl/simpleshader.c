/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simpleshader.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/22 12:25:59 by fnieto            #+#    #+#             */
/*   Updated: 2016/03/26 21:35:17 by jbyttner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

const char	vertsrc[] = ("\
		#version 330 core\n\
		\n\
		layout(location = 0) in vec2 pos;\n\
\n\
		void	main()\n\
		{\n\
			gl_Position = vec4(pos, 0, 1);\n\
		}\n\
		\0");

const char	fragsrc[] = ("\
		#version 330 core\n\
\n\
		uniform ivec2 iResolution;\n\
		\n\
		layout(location = 0) out vec4 outcol;\n\
\n\
		void	main()\n\
		{\n\
			vec2 uv = gl_FragCoord.xy / iResolution;\n\
			outcol = vec4(uv, 0, 1);\n\
			if (length(uv) > 1)\n\
				outcol.xy = vec2(0);\n\
		}\n\
		\0");
