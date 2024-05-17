/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_pointer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 17:00:16 by amakinen          #+#    #+#             */
/*   Updated: 2024/05/17 12:06:01 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal.h"

bool	format_p(t_printf_state *s)
{
	uintptr_t	p;
	char		digits[18];
	size_t		len;

	p = (uintptr_t)va_arg(s->args, const void *);
	digits[0] = '0';
	digits[1] = 'x';
	len = 2 + ptoa_arr_base(p, digits + 2, "0123456789abcdef", 16);
	return (write_simple(s, digits, len));
}
