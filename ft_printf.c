/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 11:28:27 by amakinen          #+#    #+#             */
/*   Updated: 2024/05/07 15:36:13 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "ft_printf_internal.h"

static bool	handle_specifier(t_printf_state *s)
{
	bool		success;
	t_specifier	spec;

	if (!parse_specifier(s, &spec))
		return (false);
	if (*s->fmt == 'c')
		success = format_c(s, &spec);
	else if (*s->fmt == 's')
		success = format_s(s, &spec);
	else if (*s->fmt == 'p')
		success = format_p(s, &spec);
	else if (*s->fmt == 'd' || *s->fmt == 'i')
		success = format_d(s, &spec);
	else if (*s->fmt == 'u')
		success = format_u(s, &spec);
	else if (*s->fmt == 'x')
		success = format_x(s, &spec);
	else if (*s->fmt == 'X')
		success = format_x_upper(s, &spec);
	else if (*s->fmt == '%')
		success = format_percent(s, &spec);
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
