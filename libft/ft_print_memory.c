/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_memory.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/04 09:11:05 by fnieto            #+#    #+#             */
/*   Updated: 2015/12/04 09:35:06 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	print_hex(unsigned char hex)
{
	char	*tab;

	tab = "0123456789abcdef";
	ft_putchar(tab[hex / 16]);
	ft_putchar(tab[hex % 16]);
}

static void	print_char(unsigned char hex)
{
	if (hex > 31 && hex < 127)
		ft_putchar(hex);
	else
		ft_putchar('.');
}

static void	make_hexs(unsigned char *line, size_t curline, size_t size)
{
	size_t	i;

	i = 0;
	while (i < 16)
	{
		if (i && i % 2 == 0)
			ft_putchar(' ');
		if (curline * 16 + i < size)
			print_hex(line[i]);
		else
			ft_putstr("  ");
		i++;
	}
}

void		ft_print_memory(const void *addr, size_t size)
{
	size_t			curline;
	unsigned char	*tmp;
	size_t			i;

	curline = 0;
	tmp = (unsigned char*)addr;
	while (curline * 16 < size)
	{
		make_hexs(tmp, curline, size);
		ft_putchar(' ');
		i = 0;
		while (i < 16)
		{
			if (curline * 16 + i < size)
				print_char(tmp[i]);
			i++;
		}
		ft_putchar('\n');
		tmp += 16;
		curline++;
	}
}
