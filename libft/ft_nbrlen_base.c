/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbrlen_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 17:43:10 by fnieto            #+#    #+#             */
/*   Updated: 2015/12/02 18:00:33 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_nbrlen_base(int nbr, size_t base)
{
	int		cnt;

	if (base < 2 || nbr == 0)
		return (base < 2 ? 0 : 1);
	cnt = nbr < 0;
	while (nbr)
	{
		cnt++;
		nbr /= base;
	}
	return (cnt);
}
