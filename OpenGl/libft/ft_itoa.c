/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <fnieto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 18:21:49 by fnieto            #+#    #+#             */
/*   Updated: 2015/12/04 07:12:23 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	int		len;
	int		tmp;
	char	*res;

	tmp = n;
	len = ft_nbrlen(n);
	res = ft_strnew(len);
	if (!res)
		return (0);
	tmp = 0;
	if (n < 0)
		res[0] = '-';
	res[len--] = 0;
	if (n == 0)
		res[len--] = '0';
	while (n)
	{
		res[len--] = (n < 0 ? '0' - (n % 10) : '0' + (n % 10));
		n /= 10;
	}
	return (res);
}
