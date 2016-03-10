/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cudasync.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 23:36:09 by fnieto            #+#    #+#             */
/*   Updated: 2016/03/10 20:37:38 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <stdlib.h>

t_smem		*malloc_smem(size_t size)
{
	t_smem	*n;
	int		i;

	if (!size)
		return (0);
	n = (t_smem*)malloc(sizeof(t_smem));
	if (n)
	{
		n->size = size;
		n->host = malloc(size);
		i = -1;
		while (++i < size)
			((unsigned char*)n->host)[i] = 0;
		cudaerr(cudaMalloc(&(n->device), size), __FILE__, __LINE__);
	}
	return (n);
}

void		free_smem(t_smem **mem)
{
	t_smem	*old;

	old = *mem;
	free(old->host);
	cudaerr(cudaFree(old->device), __FILE__, __LINE__);
	free(old);
	*mem = 0;
}

void		sync_host(t_smem *mem)
{
	cudaerr(cudaMemcpy(mem->host, mem->device, mem->size,
		cudaMemcpyDeviceToHost), __FILE__, __LINE__);
}

void		sync_device(t_smem *mem)
{
	cudaerr(cudaMemcpy(mem->device, mem->host, mem->size,
		cudaMemcpyHostToDevice), __FILE__, __LINE__);
}
