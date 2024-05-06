/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   integer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 16:49:13 by amakinen          #+#    #+#             */
/*   Updated: 2024/05/06 19:06:44 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internal.h"
#include "libft.h"

static int	utoa_arr_b(unsigned int n, char *arr, char *base, size_t nbase)
{
	int	len;

	len = 0;
	if (n >= nbase)
		len += utoa_arr_b(n / nbase, arr, base, nbase);
	arr[len] = base[n % nbase];
	return (len + 1);
}

bool	format_unsigned(t_printf_state *s, char *base)
{
	size_t			nbase;
	size_t			len;
	char			arr[32];
	unsigned int	n;

	n = va_arg(s->args, unsigned int);
	nbase = ft_strlen(base);
	len = utoa_arr_b(n, arr, base, nbase);
	if (!check_write(s, arr, len))
		return (false);
	return (true);
}

bool	format_signed(t_printf_state *s, char *base)
{
	size_t	nbase;
	size_t	len;
	char	arr[33];
	int		n;

	n = va_arg(s->args, int);
	nbase = ft_strlen(base);
	if (n < 0)
	{
		arr[0] = '-';
		len = 1 + utoa_arr_b(-(unsigned int)n, arr + 1, base, nbase);
	}
	else
		len = utoa_arr_b(n, arr, base, nbase);
	if (!check_write(s, arr, len))
		return (false);
	return (true);
}
