/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/01 18:32:04 by fnieto            #+#    #+#             */
/*   Updated: 2015/12/04 07:31:29 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memdup(void const *s, size_t size)
{
	void	*out;

	out = ft_memalloc(size);
	return (out ? ft_memcpy(out, s, size) : 0);
}
