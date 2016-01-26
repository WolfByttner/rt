/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/04 09:49:05 by fnieto            #+#    #+#             */
/*   Updated: 2015/12/04 09:59:27 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa_base(int n, const char *base)
{
	int		len;
	int		tmp;
	int		blen;
	char	*res;

	tmp = n;
	blen = ft_strlen(base);
	if (blen < 2)
		return (0);
	len = ft_nbrlen_base(n, blen);
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
		res[len--] = base[(n < 0 ? -(n % blen) : (n % blen))];
		n /= blen;
	}
	return (res);
}
