/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <fnieto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 17:22:34 by fnieto            #+#    #+#             */
/*   Updated: 2015/12/04 08:56:21 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

size_t static	numsplit(char const *s, char c)
{
	size_t	n;

	n = 0;
	while (*s)
	{
		if (*s != c && (s[1] == c || s[1] == 0))
			n++;
		s++;
	}
	return (n);
}

char			**ft_strsplit(char const *s, char c)
{
	char	*tmp1;
	char	*tmp2;
	char	**res;
	size_t	n;

	res = (char**)ft_memalloc((numsplit(s, c) + 1) * sizeof(char*));
	if (!res)
		return (res);
	tmp1 = (char*)s;
	n = 0;
	while (*tmp1)
		if (*tmp1 == c)
			tmp1++;
		else if (tmp1 == s || tmp1[-1] == c)
		{
			tmp2 = ft_strchr(tmp1, c);
			if (!tmp2)
				tmp2 = tmp1 + ft_strlen(tmp1);
			res[n] = ft_strnew(tmp2 - tmp1);
			ft_strncpy(res[n], tmp1, tmp2 - tmp1);
			res[n++][tmp2 - tmp1] = 0;
			tmp1 = tmp2;
		}
	return (res);
}
