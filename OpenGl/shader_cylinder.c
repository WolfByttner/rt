/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader_cylinder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/24 13:51:51 by fnieto            #+#    #+#             */
/*   Updated: 2016/04/24 13:52:43 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**cylinder is just a special case of the cone
*/

s_res		cylinder_dst(s_geo sp, s_cam cam, s_res prev)
{
	return (cone_dst(sp, cam, prev));
}
