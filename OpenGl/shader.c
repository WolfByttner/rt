/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/22 11:13:38 by fnieto            #+#    #+#             */
/*   Updated: 2016/03/22 12:25:12 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

GLuint		shader

(GLenum type,
 GLsizei count,
 GLchar **string,
 GLint *length)

{
	GLuint			id;
	GLint			status;
	GLchar			log[4097];

	id = glCreateShader(type);
	glShaderSource(id, count, (const GLchar**)string, length);
	glCompileShader(id);
	glGetShaderiv(id, GL_COMPILE_STATUS, &status);
	if(status == GL_FALSE)
	{
		glGetShaderInfoLog(id, 4096, 0, log);
		err(log);
	}
	return (id);
}

GLuint		shader_program(GLuint *shaders, size_t size)
{
	GLuint			id;

	id = glCreateProgram();
	while (size--)
		glAttachShader(id, *shaders++);
	glLinkProgram(id);
	glValidateProgram(id);
	return (id);
}
