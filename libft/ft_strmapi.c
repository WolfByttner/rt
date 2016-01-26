/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <fnieto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 15:10:33 by fnieto            #+#    #+#             */
/*   Updated: 2015/12/01 17:27:29 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	char	*res;
	char	*tmp;

	i = 0;
	res = ft_strnew(ft_strlen(s));
	if (!res)
		return (0);
	tmp = res;
	while (*s)
		*tmp++ = (*f)(i++, *s++);
	return (res);
}
