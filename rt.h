/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/26 18:42:50 by fnieto            #+#    #+#             */
/*   Updated: 2016/01/26 19:36:06 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include "fred_gl.h"

typedef	struct				s_mlx
{
	void	*core;
	void	*window;
	void	*frame;
}							t_mlx;

typedef	struct				s_params
{
	t_vec2	res;
	int		ac;
	char	**av;
}							t_params;

#endif
