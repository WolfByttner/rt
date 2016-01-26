/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gl_matrix.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/14 11:28:32 by fnieto            #+#    #+#             */
/*   Updated: 2016/01/18 19:08:45 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fred_gl.h"
#include "libft.h"
#include <stdlib.h>

static t_list	**mats(int mat)
{
	static t_list	*mats[2] = {0, 0};

	return (&(mats[mat]));
}

void			gl_pushmatrix(t_mat4 matrix)
{
	ft_lstpush(mats(gl_matrix_mode(-1)), ft_lstnew(&matrix, sizeof(t_mat4)));
}

void			gl_popmatrix(void)
{
	t_list	*tmp;

	tmp = ft_lstpop(mats(gl_matrix_mode(-1)));
	if (tmp)
	{
		free(tmp->content);
		free(tmp);
	}
}

int				gl_matrix_mode(int mat_mode)
{
	static int	mode = 0;

	if (mat_mode > -1)
		mode = CLAMP(mat_mode, 0, 1);
	return (mode);
}

t_vertex		gl_transform(t_vertex v)
{
	size_t	i;
	t_list	*tmp;

	i = -1;
	while (++i < 2)
	{
		tmp = *mats(i);
		while (tmp)
		{
			v.pos = mul_mat4_vec3(*((t_mat4*)(tmp->content)), v.pos);
			tmp = tmp->next;
		}
	}
	return (v);
}
