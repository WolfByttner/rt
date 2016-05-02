/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_fragment.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbyttner <jbyttner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/27 18:53:22 by jbyttner          #+#    #+#             */
/*   Updated: 2016/05/02 23:16:53 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

GLchar				*get_frag_params(void)
{
	static GLchar	*src = ("uniform ivec2 iResolution;\n"

	"uniform vec3 iCameraPosition = vec3(0, 0, 0);\n"
	"uniform vec2 iCameraRotation = vec2(0, 0);\n"
	"uniform float iCameraZoom = 1;\n"
	"uniform float iGlobalTime = 0;\n"
	"layout (location = 0) out vec4 outcol;\n");
	return (src);
}

void				printsrc(GLchar **src, int size)
{
	int					i;

	i = -1;
	while (++i < size)
		ft_putstr(src[i]);
}

GLuint				load_fragment(char *map)
{
	GLint				sizes[20];
	GLchar				*srcs[20];

	load_file("fragment.h", &(srcs[0]), &(sizes[0]));
	srcs[0] = ft_strjoin("#version 330 core\n", srcs[0]);
	sizes[0] += 18;
	srcs[1] = get_frag_params();
	sizes[1] = 0;
	load_file(!map ? "shader_default_map" : map, &(srcs[2]), &(sizes[2]));
	load_file("shader_quadratic.c", &(srcs[3]), &(sizes[3]));
	load_file("shader_iterate.c", &(srcs[4]), &(sizes[4]));
	load_file("shader_paint.c", &(srcs[5]), &(sizes[5]));
	load_file("shader_render_lights.c", &(srcs[6]), &(sizes[6]));
	load_file("shader_raytrace.c", &(srcs[7]), &(sizes[7]));
	load_file("shader_mobius.c", &(srcs[8]), &(sizes[8]));
	load_file("shader_box.c", &(srcs[9]), &(sizes[9]));
	load_file("shader_cone.c", &(srcs[10]), &(sizes[10]));
	load_file("shader_cylinder.c", &(srcs[11]), &(sizes[11]));
	load_file("shader_ellipse.c", &(srcs[12]), &(sizes[12]));
	load_file("shader_plane.c", &(srcs[13]), &(sizes[13]));
	load_file("shader_sphere.c", &(srcs[14]), &(sizes[14]));
	load_file("shader_klein.c", &(srcs[15]), &(sizes[15]));
	load_file("shader_heart.c", &(srcs[16]), &(sizes[16]));
	load_file("shader_noise.c", &(srcs[17]), &(sizes[17]));
	load_file("shader_torus.c", &(srcs[18]), &(sizes[18]));
	load_file("shader_main.c", &(srcs[19]), &(sizes[19]));
	printsrc(srcs, 20);
	return (shader(GL_FRAGMENT_SHADER, 20, srcs, 0));
}
