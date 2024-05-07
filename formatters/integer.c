/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   integer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 16:49:13 by amakinen          #+#    #+#             */
/*   Updated: 2024/05/07 15:39:48 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internal.h"
#include "libft.h"

#define BASE_DEC "0123456789"
#define BASE_HEXL "0123456789abcdef"
#define BASE_HEXU "0123456789ABCDEF"

bool	format_d(t_printf_state *s, t_specifier *spec)
{
	size_t	len;
	char	arr[11];
	int		n;

	(void)spec;
	n = va_arg(s->args, int);
	if (n < 0)
	{
		arr[0] = '-';
		len = 1 + utoa_arr_base(-(unsigned int)n, arr + 1, BASE_DEC, 10);
	}
	else
		len = utoa_arr_base(n, arr, BASE_DEC, 10);
	return (check_write(s, arr, len));
}

bool	format_u(t_printf_state *s, t_specifier *spec)
{
	size_t			len;
	char			arr[10];
	unsigned int	n;

	(void)spec;
	n = va_arg(s->args, unsigned int);
	len = utoa_arr_base(n, arr, BASE_DEC, 10);
	return (check_write(s, arr, len));
}

bool	format_x(t_printf_state *s, t_specifier *spec)
{
	size_t			len;
	char			arr[10];
	unsigned int	n;

	(void)spec;
	n = va_arg(s->args, unsigned int);
	len = utoa_arr_base(n, arr, BASE_HEXL, 16);
	return (check_write(s, arr, len));
}

bool	format_x_upper(t_printf_state *s, t_specifier *spec)
{
	size_t			len;
	char			arr[10];
	unsigned int	n;

	(void)spec;
	n = va_arg(s->args, unsigned int);
	len = utoa_arr_base(n, arr, BASE_HEXU, 16);
	return (check_write(s, arr, len));
}
