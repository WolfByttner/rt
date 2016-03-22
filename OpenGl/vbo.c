/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vbo.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbyttner <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/21 19:49:04 by jbyttner          #+#    #+#             */
/*   Updated: 2016/03/22 16:43:04 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

GLuint	vbo(GLenum target, GLsizeiptr size, GLvoid *data, GLenum usage)
{
	GLuint		id;

	id = glGenBuffers();
	glBindBuffer(target, id);
	glBufferData(target, size, (const GLvoid*)data, usage);
	return (id);
}

GLuint	index_buffer(GLvoid *data, GLsizeiptr size)
{
	return (vbo(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

GLuint	data_buffer(GLvoid *data, GLsizeiptr size)
{
	return (vbo(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}
