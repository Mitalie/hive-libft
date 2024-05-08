/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pointer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 17:00:16 by amakinen          #+#    #+#             */
/*   Updated: 2024/05/08 11:21:23 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internal.h"

bool	format_p(t_printf_state *s, t_specifier *spec)
{
	size_t		len;
	char		arr[18];
	const void	*p;

	(void)spec;
	p = va_arg(s->args, const void *);
	arr[0] = '0';
	arr[1] = 'x';
	len = 2 + ptoa_arr_base((uintptr_t)p, arr + 2, "0123456789abcdef", 16);
	return (write_simple(s, arr, len));
}
