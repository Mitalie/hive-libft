/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_shared.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 11:10:41 by amakinen          #+#    #+#             */
/*   Updated: 2024/05/17 11:44:36 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal_shared.h"
#include <errno.h>
#include <limits.h>
#include <unistd.h>

size_t	utoa_arr_base(unsigned int n, char *arr, char *base, unsigned int nb)
{
	size_t	len;

	len = 0;
	if (n >= nb)
		len += utoa_arr_base(n / nb, arr, base, nb);
	arr[len] = base[n % nb];
	return (len + 1);
}

size_t	ptoa_arr_base(uintptr_t n, char *arr, char *base, uintptr_t nb)
{
	size_t	len;

	len = 0;
	if (n >= nb)
		len += ptoa_arr_base(n / nb, arr, base, nb);
	arr[len] = base[n % nb];
	return (len + 1);
}

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

bool	write_simple(t_printf_state *s, const void *data, size_t len)
{
	if (len > (unsigned)INT_MAX - s->written)
		return (false);
	s->written += len;
	return (write_all(s->fd, data, len));
}
