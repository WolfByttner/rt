/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simpleshader.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/22 12:25:59 by fnieto            #+#    #+#             */
/*   Updated: 2016/03/22 20:57:16 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

const char	vertsrc[] = ("\
		#version 330 core\n\
		\n\
		layout(location = 0) in vec2 pos;\n\
		layout(location = 1) in vec2 tex;\n\
\n\
		out	VertexData\n\
		{\n\
			vec2 texCoord;\n\
		}	outData;\n\
\n\
		void	main()\n\
		{\n\
			gl_Position = vec4(pos, 0, 1);\n\
			outData.texCoord = tex;\n\
		}\n\
		\0");

const char	fragsrc[] = ("\
		#version 330 core\n\
\n\
		in VertexData\n\
		{\n\
			vec2 texCoord;\n\
		} inData;\n\
\n\
		layout(location = 0) out vec4 outcol;\n\
\n\
		void	main()\n\
		{\n\
			outcol = vec4(1);\n\
		}\n\
		\0");
