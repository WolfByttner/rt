/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbyttner <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/22 16:04:19 by jbyttner          #+#    #+#             */
/*   Updated: 2016/03/26 21:46:18 by jbyttner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <fcntl.h>
#include "rt.h"

void	load_file(char *file, GLchar **ptr, GLint *length)
{
	int		r;
	int		fd;
	char	buf[BUFF_LENGTH];
	char	*res;

	*length = 0;
	res = NULL;
	if ((fd = open(file, O_RDONLY)) == -1)
		err("Cannot open file!");
	while ((r = read(fd, buf, BUFF_LENGTH)) > 0)
	{
		if (!(res = realloc(res, *length + r)))
			err("No memory!");
		memcpy(res + *length, buf, r);
		*length += r;
	}
	if (r == -1)
		err("Failed reading file!");
	*ptr = res;
	close(fd);
}
