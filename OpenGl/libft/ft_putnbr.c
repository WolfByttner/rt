/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <fnieto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/28 22:02:51 by fnieto            #+#    #+#             */
/*   Updated: 2015/12/04 07:31:50 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	putnnbr(int n)
{
	if (n <= -10)
	{
		putnnbr(n / 10);
		putnnbr(n % 10);
	}
	else
	{
		ft_putchar('0' - n);
	}
}

void		ft_putnbr(int n)
{
	if (n < 0)
	{
		ft_putchar('-');
		putnnbr(n);
		return ;
	}
	if (n >= 10)
	{
		ft_putnbr(n / 10);
		ft_putnbr(n % 10);
	}
	else
	{
		ft_putchar('0' + n);
	}
}
