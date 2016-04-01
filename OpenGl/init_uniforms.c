/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_uniforms.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbyttner <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/29 21:02:29 by jbyttner          #+#    #+#             */
/*   Updated: 2016/04/01 15:20:25 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_input.h"

void		init_uniforms(GLuint program)
{
	t_uniforms	*u;

	u = get_uniforms();
	ft_bzero(u, sizeof *u);
	u->cammov = 10;
	u->camsr = 0.001;
	u->icampos = glGetUniformLocation(program, "iCameraPosition");
	u->icamrot = glGetUniformLocation(program, "iCameraRotation");
	u->icamzoom = glGetUniformLocation(program, "iCameraZoom");
	u->ires = glGetUniformLocation(program, "iResolution");
	u->itime = glGetUniformLocation(program, "iGlobalTime");
}
