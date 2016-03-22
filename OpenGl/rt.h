/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbyttner <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/21 19:50:48 by jbyttner          #+#    #+#             */
/*   Updated: 2016/03/22 12:25:30 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H
# include <GLFW/glfw3.h>
# include <string.h>
# define P_NAME "foobar"

void				err(char *msg);
GLuint				shader(GLenum t, GLsizei c, GLchar **s, GLint *l);
GLuint				shader_program(GLuint *shaders, size_t size);

#endif
