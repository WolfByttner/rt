/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_properties.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbyttner <jbyttner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/27 21:46:19 by jbyttner          #+#    #+#             */
/*   Updated: 2016/04/27 21:46:52 by jbyttner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_properties	*get_properties(void)
{
	static t_properties	properties;

	return (&properties);
}
