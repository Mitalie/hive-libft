/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_integer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 16:49:13 by amakinen          #+#    #+#             */
/*   Updated: 2024/05/17 14:30:09 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal.h"

#define BASE_DEC "0123456789"
#define BASE_HEXL "0123456789abcdef"
#define BASE_HEXU "0123456789ABCDEF"

bool	format_d(t_printf_state *s)
{
	int		n;
	char	digits[11];
	size_t	len;

	n = va_arg(s->args, int);
	if (n < 0)
	{
		digits[0] = '-';
		len = 1 + utoa_arr_base(-(unsigned int)n, digits + 1, BASE_DEC, 10);
	}
	else
		len = utoa_arr_base(n, digits, BASE_DEC, 10);
	return (write_simple(s, digits, len));
}

bool	format_u(t_printf_state *s)
{
	unsigned int	n;
	char			digits[10];
	size_t			len;

	n = va_arg(s->args, unsigned int);
	len = utoa_arr_base(n, digits, BASE_DEC, 10);
	return (write_simple(s, digits, len));
}

bool	format_x(t_printf_state *s)
{
	unsigned int	n;
	char			digits[8];
	size_t			len;

	n = va_arg(s->args, unsigned int);
	len = utoa_arr_base(n, digits, BASE_HEXL, 16);
	return (write_simple(s, digits, len));
}

bool	format_x_upper(t_printf_state *s)
{
	unsigned int	n;
	char			digits[8];
	size_t			len;

	n = va_arg(s->args, unsigned int);
	len = utoa_arr_base(n, digits, BASE_HEXU, 16);
	return (write_simple(s, digits, len));
}
