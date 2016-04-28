/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_size_callback.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeken <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/28 19:48:36 by mdeken            #+#    #+#             */
/*   Updated: 2016/04/28 20:23:36 by mdeken           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_input.h"

#include <stdio.h>

void	window_size_callback(GLFWwindow *window, int width, int height)
{
	t_properties	*properties;

	(void)window;
	properties = get_properties();
	properties->width = width;
	properties->height = height;
	printf("%d %d\n", width, height);
}
