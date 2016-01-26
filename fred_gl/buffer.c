/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/09 15:56:15 by fnieto            #+#    #+#             */
/*   Updated: 2016/01/09 20:36:04 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fred_gl.h"
#include "libft.h"

t_buffer		*buffer(size_t w, size_t h, size_t type)
{
	t_buffer	*new;
	void		*buf;

	buf = (void*)ft_memalloc((w * h + 1) * type);
	if (!buf)
		return (0);
	new = (t_buffer*)ft_memalloc(sizeof(t_buffer));
	if (!new)
	{
		ft_memdel((void**)&buf);
		return (0);
	}
	new->buf = buf;
	new->w = w;
	new->h = h;
	new->type = type;
	return (new);
}

t_type			buf_read(t_buffer *buf, size_t x, size_t y)
{
	t_type	new;

	ft_memcpy(&new, buf->buf + (y * buf->w + x) * buf->type, buf->type);
	return (new);
}

void			buf_write(t_buffer *buf, size_t x, size_t y, t_type val)
{
	ft_memcpy(buf->buf + (y * buf->w + x) * buf->type, &val, buf->type);
}

void			buffer_del(t_buffer **buf)
{
	t_buffer	*todel;

	todel = *buf;
	ft_memdel((void**)&(todel->buf));
	ft_memdel((void**)buf);
}
