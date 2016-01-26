/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <fnieto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 12:54:54 by fnieto            #+#    #+#             */
/*   Updated: 2015/12/09 19:16:14 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*tmp;
	unsigned char	*tmp2;
	size_t			i;

	i = -1;
	tmp = (unsigned char*)dest;
	tmp2 = (unsigned char*)src;
	if (dest < src)
		while (++i < n)
			tmp[i] = tmp2[i];
	if (dest > src)
		while (++i < n)
			tmp[n - i - 1] = tmp2[n - i - 1];
	return (dest);
}
