/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 15:04:46 by amakinen          #+#    #+#             */
/*   Updated: 2024/05/16 14:42:04 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <errno.h>
#include <limits.h>
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
	if (!newstr)
		return (cleanup(line, readbuf));
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

	if (!readbuf->buf)
		readbuf->buf = malloc(BUFFER_SIZE);
	if (!readbuf->buf)
		return (false);
	while (true)
	{
		ret = read(fd, readbuf->buf, BUFFER_SIZE);
		if (ret >= 0)
		{
			readbuf->len = ret;
			if (ret == 0)
			{
				free(readbuf->buf);
				readbuf->buf = 0;
			}
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
	static t_readbuf	readbuf[OPEN_MAX];
	t_linebuf			linebuf;
	size_t				line_len;

	if (fd < 0 || fd >= OPEN_MAX)
		return (0);
	linebuf = (t_linebuf){0};
	while (true)
	{
		if (readbuf[fd].len == 0 && !read_helper(fd, &readbuf[fd]))
			break ;
		if (find_linebreak(&readbuf[fd], &line_len))
			return (linebuf_finish(&linebuf, &readbuf[fd], line_len));
		if (!linebuf_append(&linebuf, &readbuf[fd]))
			break ;
	}
	return (cleanup(&linebuf, &readbuf[fd]));
}
