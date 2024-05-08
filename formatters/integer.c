/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   integer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 16:49:13 by amakinen          #+#    #+#             */
/*   Updated: 2024/05/08 13:55:31 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internal.h"
#include "libft.h"

#define BASE_DEC "0123456789"
#define BASE_HEXL "0123456789abcdef"
#define BASE_HEXU "0123456789ABCDEF"

bool	format_d(t_printf_state *s, t_specifier *spec)
{
	int			n;
	char		digits[10];
	t_number	num;

	num = (t_number){digits, 0, "-", 1};
	n = va_arg(s->args, int);
	if (n < 0)
		num.digits_len = utoa_arr_base(-(unsigned int)n, digits, BASE_DEC, 10);
	else
	{
		if (n != 0 || !spec->use_precision || spec->precision != 0)
			num.digits_len = utoa_arr_base(n, digits, BASE_DEC, 10);
		if (spec->sign_mode == SIGN_BLANK)
			num.prefix = " ";
		else if (spec->sign_mode == SIGN_PLUS)
			num.prefix = "+";
		else
			num.prefix_len = 0;
	}
	return (write_number(s, spec, num));
}

bool	format_u(t_printf_state *s, t_specifier *spec)
{
	unsigned int	n;
	char			digits[10];
	t_number		num;

	num = (t_number){digits, 0, 0, 0};
	n = va_arg(s->args, unsigned int);
	if (n != 0 || !spec->use_precision || spec->precision != 0)
		num.digits_len = utoa_arr_base(n, digits, BASE_DEC, 10);
	return (write_number(s, spec, num));
}

bool	format_x(t_printf_state *s, t_specifier *spec)
{
	unsigned int	n;
	char			digits[8];
	t_number		num;

	num = (t_number){digits, 0, "0x", 0};
	n = va_arg(s->args, unsigned int);
	if (n != 0 || !spec->use_precision || spec->precision != 0)
		num.digits_len = utoa_arr_base(n, digits, BASE_HEXL, 16);
	if (n != 0 && spec->alternate)
		num.prefix_len = 2;
	return (write_number(s, spec, num));
}

bool	format_x_upper(t_printf_state *s, t_specifier *spec)
{
	unsigned int	n;
	char			digits[8];
	t_number		num;

	num = (t_number){digits, 0, "0X", 0};
	n = va_arg(s->args, unsigned int);
	if (n != 0 || !spec->use_precision || spec->precision != 0)
		num.digits_len = utoa_arr_base(n, digits, BASE_HEXU, 16);
	if (n != 0 && spec->alternate)
		num.prefix_len = 2;
	return (write_number(s, spec, num));
}
