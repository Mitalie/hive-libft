/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_pointer_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 17:00:16 by amakinen          #+#    #+#             */
/*   Updated: 2024/05/17 11:52:11 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal_bonus.h"

bool	format_p(t_printf_state *s, t_specifier *spec)
{
	uintptr_t	p;
	char		digits[16];
	t_number	num;

	num = (t_number){digits, 0, "0x", 2};
	p = (uintptr_t)va_arg(s->args, const void *);
	if (p || !spec->use_precision || spec->precision != 0)
		num.digits_len = ptoa_arr_base(p, digits, "0123456789abcdef", 16);
	else
		num.digits_len = 0;
	return (write_number(s, spec, num));
}
