/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <fnieto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 19:40:38 by fnieto            #+#    #+#             */
/*   Updated: 2015/12/06 16:32:24 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strstr(const char *haystack, const char *needle)
{
	const char	*tmp1;
	const char	*tmp2;

	while (*haystack)
	{
		tmp1 = haystack;
		tmp2 = needle;
		while (*tmp1 && *tmp2 && *tmp1 == *tmp2)
		{
			tmp1++;
			tmp2++;
		}
		if (!*tmp2)
			return ((char*)haystack);
		if (!*tmp1)
			return (0);
		haystack++;
	}
	return ((*haystack == 0 && *needle == 0) ? (char*)haystack : 0);
}
