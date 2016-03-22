/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <fnieto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/28 22:51:13 by fnieto            #+#    #+#             */
/*   Updated: 2015/12/04 07:29:49 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*tmp;
	t_list	*tmp2;

	if (!alst || !(*alst) || !del)
		return ;
	tmp = *alst;
	while (tmp)
	{
		tmp2 = tmp;
		tmp = tmp->next;
		ft_lstdelone(&tmp2, del);
	}
	*alst = 0;
}
