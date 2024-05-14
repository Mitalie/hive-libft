/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 15:46:00 by amakinen          #+#    #+#             */
/*   Updated: 2024/05/14 15:01:14 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <errno.h>
#include <stdlib.h>

static size_t	get_line_len(const char *buf, size_t len)
{
	size_t	idx;

	idx = 0;
	while (idx < len && buf[idx] != '\n')
		idx++;
	if (idx == len)
		return (0);
	return (idx + 1);
}

static bool	append_to_line(t_linebuf *line, const char *data, size_t len)
{
	char	*newbuf;

	if (len > line->alloc - line->len)
	{
		if (!line->alloc)
			line->alloc = BUFFER_SIZE;
		while (len > line->alloc - line->len)
			line->alloc *= 2;
		newbuf = malloc(line->alloc);
		if (newbuf)
			ft_memcpy(newbuf, line->buf, line->len);
		free(line->buf);
		line->buf = newbuf;
	}
	if (len && !line->buf)
		return (false);
	ft_memcpy(line->buf + line->len, data, len);
	line->len += len;
	return (true);
}

static char	*complete_line(t_linebuf *line, const char *data, size_t line_len)
{
	char	*newstr;

	if (line->len == 0 && line_len == 0)
		return (0);
	newstr = malloc(line->len + line_len + 1);
	if (newstr)
	{
		ft_memcpy(newstr, line->buf, line->len);
		ft_memcpy(newstr + line->len, data, line_len);
		newstr[line->len + line_len] = 0;
	}
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
	static t_readbuf	readbuf = {0};
	t_linebuf			linebuf;
	size_t				line_len;
	char				*line;

	linebuf = (t_linebuf){0};
	line_len = get_line_len(readbuf.buf, readbuf.len);
	while (!line_len)
	{
		if (!append_to_line(&linebuf, readbuf.buf, readbuf.len))
			return (0);
		if (!read_helper(fd, &readbuf))
		{
			free(linebuf.buf);
			return (0);
		}
		line_len = get_line_len(readbuf.buf, readbuf.len);
		if (readbuf.len == 0)
			break ;
	}
	line = complete_line(&linebuf, readbuf.buf, line_len);
	readbuf.len -= line_len;
	ft_memcpy(readbuf.buf, readbuf.buf + line_len, readbuf.len);
	return (line);
}
