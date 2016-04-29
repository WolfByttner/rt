/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_size_callback.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeken <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/28 19:48:36 by mdeken            #+#    #+#             */
/*   Updated: 2016/04/29 17:16:48 by mdeken           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_input.h"

/*
** Whenever the window is resized window_size_callback is called, and saves
** the new width and height of the window.
*/

void	window_size_callback(GLFWwindow *window, int width, int height)
{
	t_properties	*properties;

	(void)window;
	properties = get_properties();
	properties->width = width;
	properties->height = height;
}
