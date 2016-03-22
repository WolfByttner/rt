/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simpleshader.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/22 12:25:59 by fnieto            #+#    #+#             */
/*   Updated: 2016/03/22 12:53:10 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

const static char	*vertsrc = ("
		#version 400 core
		
		layout(location = 0) in vec2 pos;
		layout(location = 1) in vec2 tex;

		out	VertexData
		{
			vec2 texCoords;
		}	outData;

		void	main()
		{
			gl_position = vec4(pos, 0, 0);
			outData.texCoord = tex;
		}
		");

const static char	*fragsrc = ("
		#version 400 core

		in VertexData
		{
			vec2 texCoord;
		} inData;

		layout(location = 0) out vec4 outcol;

		void	main()
		{
			outcol = vec4(inData.texCoord, 0, 1);
		}
		")
