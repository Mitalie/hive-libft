/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_write.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 18:03:41 by amakinen          #+#    #+#             */
/*   Updated: 2024/05/06 18:26:02 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internal.h"
#include <errno.h>
#include <limits.h>
#include <unistd.h>

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

bool	check_write(int *written, const void *data, size_t len)
{
	if (len > (unsigned)INT_MAX - *written)
		return (false);
	*written += len;
	return (write_retry(STDOUT_FILENO, data, len));
}
