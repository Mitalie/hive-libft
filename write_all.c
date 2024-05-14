/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_all.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 10:47:41 by amakinen          #+#    #+#             */
/*   Updated: 2024/05/14 10:51:41 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internal.h"
#include <errno.h>
#include <unistd.h>

/*
	Write the entire buffer into given file descriptor, retrying interrupted
	system calls and short writes. Returns true on success and false on error.
*/
bool	write_all(int fd, const void *buf, size_t len)
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
