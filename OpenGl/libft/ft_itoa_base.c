/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/04 09:49:05 by fnieto            #+#    #+#             */
/*   Updated: 2016/04/07 16:02:06 by jbyttner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa_base(int n, const char *base)
{
	int		len;
	int		blen;
	char	*res;

	blen = ft_strlen(base);
	if (blen < 2)
		return (0);
	len = ft_nbrlen_base(n, blen);
	res = ft_strnew(len);
	if (!res)
		return (0);
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
