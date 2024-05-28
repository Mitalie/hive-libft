/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 15:46:00 by amakinen          #+#    #+#             */
/*   Updated: 2024/05/28 10:49:26 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <errno.h>
#include <stdint.h>
#include <stdlib.h>

static bool	buf_ensure_space(t_buf *buf, size_t space)
{
	void	*new_alloc;

	if (buf->len > SIZE_MAX - space)
		return (false);
	space += buf->len;
	if (buf->alloc >= space)
		return (true);
	if (buf->alloc == 0)
		buf->alloc = space;
	while (buf->alloc < space && buf->alloc <= SIZE_MAX / 2)
		buf->alloc *= 2;
	if (buf->alloc < space)
		buf->alloc = SIZE_MAX;
	new_alloc = malloc(buf->alloc);
	if (new_alloc)
		ft_memcpy(new_alloc, buf->buf, buf->len);
	free(buf->buf);
	buf->buf = new_alloc;
	return (buf->buf != 0);
}

static bool	do_read(int fd, t_buf *buf, size_t *read_len)
{
	ssize_t	ret;

	if (!buf_ensure_space(buf, BUFFER_SIZE))
		return (false);
	while (true)
	{
		ret = read(fd, buf->buf + buf->len, BUFFER_SIZE);
		if (ret < 0 && errno == EINTR)
			continue ;
		if (ret < 0)
			return (false);
		buf->len += ret;
		*read_len = ret;
		return (true);
	}
}

/*
	The newline character is considered part of the line, a null character is
	not because caller of get_next_line can not recognize it in a C string. It
	will stay in the buffer, resulting in line_len of 0 on next call.
*/
static bool	find_line(t_buf *buf, size_t read_len, size_t *line_len)
{
	char	*start;
	size_t	idx;

	*line_len = buf->len;
	if (read_len == 0)
		return (true);
	*line_len -= read_len;
	start = buf->buf + buf->len - read_len;
	idx = 0;
	while (idx < read_len)
	{
		if (start[idx] == '\n')
		{
			*line_len += idx + 1;
			return (true);
		}
		if (start[idx] == '\0')
		{
			*line_len += idx;
			return (true);
		}
		idx++;
	}
	return (false);
}

/*
	If line_len is 0 there's a null character at the front of the buffer; emit
	it alone as an empty string and consume it from the buffer. Empty strings
	are only emitted as a result of null characters, so caller of get_next_line
	can reliably interpret empty strings as null characters.
*/
static char	*split_line(t_buf *buf, size_t line_len)
{
	char	*str;
	void	*rest;
	size_t	rest_len;

	str = malloc(line_len + 1);
	if (str)
		str[line_len] = 0;
	if (line_len == 0)
		line_len++;
	rest_len = buf->len - line_len;
	rest = malloc(rest_len);
	if (!str || !rest)
	{
		free(str);
		free(rest);
		free(buf->buf);
		*buf = (t_buf){0};
		return (0);
	}
	ft_memcpy(str, buf->buf, line_len);
	ft_memcpy(rest, buf->buf + line_len, rest_len);
	free(buf->buf);
	*buf = (t_buf){rest, rest_len, rest_len};
	return (str);
}

char	*get_next_line(int fd)
{
	static t_buf	buf;
	size_t			read_len;
	size_t			line_len;

	read_len = buf.len;
	while (true)
	{
		if (buf.len && find_line(&buf, read_len, &line_len))
			return (split_line(&buf, line_len));
		if (!do_read(fd, &buf, &read_len))
			break ;
		if (!read_len && !buf.len)
			break ;
	}
	free(buf.buf);
	buf = (t_buf){0};
	return (0);
}
