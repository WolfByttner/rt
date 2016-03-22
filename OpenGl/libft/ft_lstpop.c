/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 18:09:28 by fnieto            #+#    #+#             */
/*   Updated: 2016/01/12 18:18:10 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstpop(t_list **alst)
{
	t_list	*tmp;
	t_list	*rem;

	if (!(*alst))
		return (0);
	tmp = *alst;
	if (!(tmp->next))
	{
		*alst = 0;
		return (tmp);
	}
	while (tmp->next->next)
		tmp = tmp->next;
	rem = tmp->next;
	tmp->next = 0;
	return (rem);
}
