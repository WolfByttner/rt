/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 19:50:44 by fnieto            #+#    #+#             */
/*   Updated: 2016/03/10 19:52:14 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int		isblank(int c)
{
	return (c == ' ' || c == '\n' || c == '\t' || c == '\v' || c == '\f'
		|| c == '\r');
}

int				ft_atoi(const char *str)
{
	int		res;
	int		neg;

	res = 0;
	while (isblank(*str))
		++str;
	neg = *str == '-';
	if (*str == '+' || *str == '-')
		++str;
	while (*str >= '0' && *str <= '9')
		res = res * 10 - (*str++ - '0');
	return (neg ? res : -res);
}
