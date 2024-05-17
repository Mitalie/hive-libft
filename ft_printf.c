/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 11:28:27 by amakinen          #+#    #+#             */
/*   Updated: 2024/05/17 11:22:09 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "ft_printf_internal.h"
#include <unistd.h>

static bool	print_until_specifier(t_printf_state *s)
{
	size_t	len;

	len = 0;
	while (s->fmt[len] && s->fmt[len] != '%')
		len++;
	if (!write_simple(s, s->fmt, len))
		return (false);
	s->fmt += len;
	return (true);
}

int	ft_printf(const char *fmt, ...)
{
	t_printf_state	s;
	bool			success;

	s.fd = STDOUT_FILENO;
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
