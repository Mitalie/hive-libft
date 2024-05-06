/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pointer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 17:00:16 by amakinen          #+#    #+#             */
/*   Updated: 2024/05/06 17:52:54 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internal.h"
#include "libft.h"
#include <stdint.h>
#include <unistd.h>

static int	ptoa_arr_b(uintptr_t n, char *arr, char *base, size_t nbase)
{
	size_t	len;

	len = 0;
	if (n >= nbase)
		len += ptoa_arr_b(n / nbase, arr, base, nbase);
	arr[len] = base[n % nbase];
	return (len + 1);
}

bool	format_pointer(int *written, void *p)
{
	size_t	len;
	char	arr[18];

	arr[0] = '0';
	arr[1] = 'x';
	len = 2 + ptoa_arr_b((uintptr_t)p, arr + 2, "0123456789abcdef", 16);
	if (write(STDOUT_FILENO, arr, len) < 0)
		return (false);
	*written += len;
	return (true);
}
