/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <fnieto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 19:30:35 by fnieto            #+#    #+#             */
/*   Updated: 2015/12/04 08:21:14 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*tmp;

	tmp = (char*)s + ft_strlen(s);
	while (tmp >= s)
	{
		if (*tmp == c)
			return (tmp);
		tmp--;
	}
	return (0);
}
