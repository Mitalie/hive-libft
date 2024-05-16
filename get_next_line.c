/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 15:46:00 by amakinen          #+#    #+#             */
/*   Updated: 2024/05/16 14:22:54 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <errno.h>
#include <stdint.h>
#include <stdlib.h>

static bool	find_linebreak(t_readbuf *readbuf, size_t *line_len)
{
	size_t	idx;

	*line_len = 0;
	if (readbuf->len == 0)
		return (true);
	idx = 0;
	while (idx < readbuf->len && readbuf->buf[idx] != '\n' && readbuf->buf[idx])
		idx++;
	if (idx == readbuf->len)
		return (false);
	*line_len = idx + 1;
	return (true);
}

static bool	linebuf_append(t_linebuf *line, t_readbuf *readbuf)
{
	size_t	len;

	len = readbuf->len;
	readbuf->len = 0;
	if (len > SIZE_MAX - line->len)
	{
		free(line->buf);
		return (false);
	}
	if (len > line->alloc - line->len)
	{
		if (line->alloc == 0)
			line->alloc = BUFFER_SIZE;
		while (len > line->alloc - line->len && line->alloc <= SIZE_MAX / 2)
			line->alloc *= 2;
		if (len > line->alloc - line->len)
			line->alloc = SIZE_MAX;
		line->buf = ft_reallocf(line->buf, line->alloc, line->len);
	}
	if (len && !line->buf)
		return (false);
	ft_memcpy(line->buf + line->len, readbuf->buf, len);
	line->len += len;
	return (true);
}

static char	*linebuf_finish(t_linebuf *line, t_readbuf *readbuf,
	size_t line_len)
{
	char	*newstr;

	if (line->len == 0 && line_len == 0 && !readbuf->prev_nullterm)
		return (0);
	newstr = bufs_to_str(line->buf, line->len, readbuf->buf, line_len);
	readbuf->prev_nullterm = false;
	if (line_len && readbuf->buf[line_len - 1] == 0)
		readbuf->prev_nullterm = true;
	readbuf->len -= line_len;
	ft_memcpy(readbuf->buf, readbuf->buf + line_len, readbuf->len);
	free(line->buf);
	return (newstr);
}

static bool	read_helper(int fd, t_readbuf *readbuf)
{
	ssize_t	ret;

	while (true)
	{
		ret = read(fd, readbuf->buf, sizeof readbuf->buf);
		if (ret >= 0)
		{
			readbuf->len = ret;
			return (true);
		}
		else if (ret < 0 && errno != EINTR)
		{
			readbuf->len = 0;
			return (false);
		}
	}
}

char	*get_next_line(int fd)
{
	static t_readbuf	readbuf;
	t_linebuf			linebuf;
	size_t				line_len;

	linebuf = (t_linebuf){0};
	while (true)
	{
		if (readbuf.len == 0 && !read_helper(fd, &readbuf))
			break ;
		if (find_linebreak(&readbuf, &line_len))
			return (linebuf_finish(&linebuf, &readbuf, line_len));
		if (!linebuf_append(&linebuf, &readbuf))
			return (0);
	}
	free(linebuf.buf);
	return (0);
}
