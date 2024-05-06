/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   integer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 16:49:13 by amakinen          #+#    #+#             */
/*   Updated: 2024/05/06 17:54:13 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internal.h"
#include "libft.h"
#include <unistd.h>

static int	utoa_arr_b(unsigned int n, char *arr, char *base, size_t nbase)
{
	int	len;

	len = 0;
	if (n >= nbase)
		len += utoa_arr_b(n / nbase, arr, base, nbase);
	arr[len] = base[n % nbase];
	return (len + 1);
}

bool	format_unsigned(int *written, unsigned int n, char *base)
{
	size_t	nbase;
	size_t	len;
	char	arr[32];

	nbase = ft_strlen(base);
	len = utoa_arr_b(n, arr, base, nbase);
	if (write(STDOUT_FILENO, arr, len) < 0)
		return (false);
	*written += len;
	return (true);
}

bool	format_signed(int *written, int n, char *base)
{
	size_t	nbase;
	size_t	len;
	char	arr[33];

	nbase = ft_strlen(base);
	if (n < 0)
	{
		arr[0] = '-';
		len = 1 + utoa_arr_b(-(unsigned int)n, arr + 1, base, nbase);
	}
	else
		len = utoa_arr_b(n, arr, base, nbase);
	if (write(STDOUT_FILENO, arr, len) < 0)
		return (false);
	*written += len;
	return (true);
}
