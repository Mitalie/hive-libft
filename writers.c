/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   writers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 18:03:41 by amakinen          #+#    #+#             */
/*   Updated: 2024/05/08 11:38:17 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internal.h"
#include <errno.h>
#include <limits.h>
#include <unistd.h>
#include "libft.h"

static bool	write_retry(int fd, const void *buf, size_t len)
{
	ssize_t	ret;

	while (len)
	{
		ret = write(fd, buf, len);
		if (ret < 0 && errno == EINTR)
			continue ;
		else if (ret < 0)
			return (false);
		buf = (char *)buf + ret;
		len -= ret;
	}
	return (true);
}

static bool	write_char_repeat(int fd, char c, size_t n)
{
	char	buf[64];

	ft_memset(buf, c, sizeof(buf));
	while (n > sizeof(buf))
	{
		if (!write_retry(fd, buf, sizeof(buf)))
			return (false);
		n -= sizeof(buf);
	}
	return (write_retry(fd, buf, n));
}

bool	write_simple(t_printf_state *s, const void *data, size_t len)
{
	if (len > (unsigned)INT_MAX - s->written)
		return (false);
	s->written += len;
	return (write_retry(s->fd, data, len));
}

bool	write_padded(t_printf_state *s, t_specifier *spec,
			const void *data, size_t len)
{
	size_t	pad_len;

	pad_len = 0;
	if (len < spec->width)
		pad_len = spec->width - len;
	if (len + pad_len > (unsigned)INT_MAX - s->written)
		return (false);
	s->written += len + pad_len;
	if (spec->pad_mode == PAD_BLANK && !write_char_repeat(s->fd, ' ', pad_len))
		return (false);
	if (!write_retry(s->fd, data, len))
		return (false);
	if (spec->pad_mode == PAD_RIGHT && !write_char_repeat(s->fd, ' ', pad_len))
		return (false);
	return (true);
}
