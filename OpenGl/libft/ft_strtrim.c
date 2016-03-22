/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <fnieto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 15:32:16 by fnieto            #+#    #+#             */
/*   Updated: 2015/12/04 07:33:09 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	const char	*tmp;
	const char	*res;

	res = s;
	while (*res && ft_any(*res, "\n\t "))
		res++;
	tmp = res + ft_strlen(res);
	while (tmp >= res && (ft_any(*tmp, "\n\t ") || *tmp == 0))
		tmp--;
	return (ft_strsub(s, res - s, tmp - res + 1));
}
