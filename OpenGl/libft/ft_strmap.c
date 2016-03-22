/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <fnieto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 15:05:55 by fnieto            #+#    #+#             */
/*   Updated: 2015/12/01 17:27:22 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*res;
	char	*tmp;

	res = ft_strnew(ft_strlen(s));
	if (!res)
		return (0);
	tmp = res;
	while (*s)
		*tmp++ = (*f)(*s++);
	return (res);
}
