/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel_if.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/05 22:08:07 by fnieto            #+#    #+#             */
/*   Updated: 2015/12/05 22:37:13 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel_if(t_list **begin_list, void *data_ref, int (*cmp)())
{
	t_list *tmp;
	t_list *dump;

	tmp = *begin_list;
	while (tmp && (*cmp)(tmp->content, tmp->content_size, data_ref) == 0)
	{
		(*begin_list) = tmp->next;
		ft_memdel((void**)&tmp);
		tmp = *begin_list;
	}
	if (tmp)
		while (tmp->next)
		{
			if ((*cmp)(tmp->next->content, tmp->next->content_size, data_ref))
				tmp = tmp->next;
			else
			{
				dump = tmp->next;
				tmp->next = dump->next;
				ft_memdel((void**)&dump);
			}
		}
}
