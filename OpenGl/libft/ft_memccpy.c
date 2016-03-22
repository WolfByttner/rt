/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <fnieto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 12:33:29 by fnieto            #+#    #+#             */
/*   Updated: 2015/12/02 18:39:45 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	unsigned char		*tmp;
	unsigned char		*tmp2;

	tmp = (unsigned char*)dest;
	tmp2 = (unsigned char*)src;
	while (n--)
		if ((*tmp++ = *tmp2++) == ((unsigned char)c))
			return (tmp);
	return (0);
}
