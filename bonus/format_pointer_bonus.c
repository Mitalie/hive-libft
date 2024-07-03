/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_pointer_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 17:00:16 by amakinen          #+#    #+#             */
/*   Updated: 2024/07/03 13:18:38 by amakinen         ###   ########.fr       */
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
	if (IS_LINUX && !p)
		return (write_padded(s, spec, "(nil)", 5));
	if (p || !spec->use_precision || spec->precision != 0)
		num.digits_len = ptoa_arr_base(p, digits, "0123456789abcdef", 16);
	else
		num.digits_len = 0;
	if (IS_LINUX && spec->sign_mode == SIGN_BLANK)
	{
		num.prefix = " 0x";
		num.prefix_len = 3;
	}
	else if (IS_LINUX && spec->sign_mode == SIGN_PLUS)
	{
		num.prefix = "+0x";
		num.prefix_len = 3;
	}
	return (write_number(s, spec, num));
}
