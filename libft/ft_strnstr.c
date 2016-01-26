/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <fnieto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 20:07:15 by fnieto            #+#    #+#             */
/*   Updated: 2015/12/04 08:33:31 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t n)
{
	const char	*tmp1;
	const char	*tmp2;
	size_t		i;

	while (*haystack && n)
	{
		tmp1 = haystack;
		tmp2 = needle;
		i = n;
		while (*tmp1 && *tmp2 && *tmp1 == *tmp2 && i)
		{
			tmp1++;
			tmp2++;
			i--;
		}
		if (!*tmp2)
			return ((char*)haystack);
		if (!*tmp1 || i <= 0)
			return (0);
		haystack++;
		n--;
	}
	return ((*haystack == 0 && *needle == 0) ? (char*)haystack : 0);
}
