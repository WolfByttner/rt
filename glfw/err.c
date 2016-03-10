/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 19:30:38 by fnieto            #+#    #+#             */
/*   Updated: 2016/03/10 21:30:26 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

void		err(char *str)
{
	while (*str)
		write(2, str++, 1);
	exit(1);
}

void		cudaerr(cudaError_t error, char *file, int line)
{
	if (error != cudaSuccess)
	{
		printf("Error: %s\n in file %s at line no %d\n",
				cudaGetErrorString(error), file, line);
		exit(EXIT_FAILURE);
	}
}
