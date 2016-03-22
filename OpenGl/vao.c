/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vao.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/22 16:06:05 by fnieto            #+#    #+#             */
/*   Updated: 2016/03/22 17:23:01 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

GLuint		vao(void)
{
	GLuint	id;

	glGenVertexArrays(1, &id);
	return (id);
}

void		vao_add_indices(GLuint vao, GLuint vbo)
{
	glBindVertexArray(vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo);
}

void		vao_add_vdata(GLuint vao, GLuint vbo, GLint size, GLboolean norm)
{
	static	GLint	index;

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(index++, size, GL_FLOAT, norm, 0, 0);
}
