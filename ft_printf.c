/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 11:28:27 by amakinen          #+#    #+#             */
/*   Updated: 2024/05/06 19:10:35 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "ft_printf_internal.h"

#define BASE_DEC "0123456789"
#define BASE_HEXL "0123456789abcdef"
#define BASE_HEXU "0123456789ABCDEF"

static bool	handle_specifier(t_printf_state *s)
{
	bool	success;

	if (*s->fmt == 'c')
		success = format_char(s);
	else if (*s->fmt == 's')
		success = format_string(s);
	else if (*s->fmt == 'p')
		success = format_pointer(s);
	else if (*s->fmt == 'd' || *s->fmt == 'i')
		success = format_signed(s, BASE_DEC);
	else if (*s->fmt == 'u')
		success = format_unsigned(s, BASE_DEC);
	else if (*s->fmt == 'x')
		success = format_unsigned(s, BASE_HEXL);
	else if (*s->fmt == 'X')
		success = format_unsigned(s, BASE_HEXU);
	else if (*s->fmt == '%')
		success = format_percent(s);
	else
		return (false);
	s->fmt++;
	return (success);
}

static bool	print_until_specifier(t_printf_state *s)
{
	size_t	len;

	len = 0;
	while (s->fmt[len] && s->fmt[len] != '%')
		len++;
	if (!check_write(s, s->fmt, len))
		return (false);
	s->fmt += len;
	return (true);
}

int	ft_printf(const char *fmt, ...)
{
	t_printf_state	s;
	bool			success;

	s.fmt = fmt;
	va_start(s.args, fmt);
	s.written = 0;
	while (*s.fmt)
	{
		if (*s.fmt == '%')
		{
			s.fmt++;
			success = handle_specifier(&s);
		}
		else
			success = print_until_specifier(&s);
		if (!success)
			return (-1);
	}
	va_end(s.args);
	return (s.written);
}
