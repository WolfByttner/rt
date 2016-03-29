/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_input.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbyttner <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/29 19:19:12 by jbyttner          #+#    #+#             */
/*   Updated: 2016/03/29 21:11:43 by jbyttner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_INPUT_H
# define RT_INPUT_H
# include "rt.h"

typedef struct		s_uniforms
{
	float			cammov;
	GLint			icampos;
	float			campos[3];
	GLint			icamrot;
	float			camrot[2];
	GLint			icamzoom;
	float			camzoom;
	GLint			ires;
	int				res[2];
	GLint			itime;
	float			time;
}					t_uniforms;

void				poll_keys(GLFWwindow *window, float ftime);

t_uniforms			*get_uniforms(void);

void				init_uniforms(GLuint program);

#endif
