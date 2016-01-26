/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <fnieto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 20:13:16 by fnieto            #+#    #+#             */
/*   Updated: 2015/12/04 08:38:02 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	len;
	size_t	tmp;

	len = ft_strlen(s1);
	tmp = ft_strlen(s2);
	len = len < tmp ? tmp : len;
	return (ft_memcmp(s1, s2, len > n ? n : len));
}
