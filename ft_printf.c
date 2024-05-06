/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 11:28:27 by amakinen          #+#    #+#             */
/*   Updated: 2024/05/06 18:05:06 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "ft_printf_internal.h"
#include <limits.h>
#include <stdarg.h>
#include <stdbool.h>
#include <unistd.h>

#define BASE_DEC "0123456789"
#define BASE_HEXL "0123456789abcdef"
#define BASE_HEXU "0123456789ABCDEF"

static bool	handle_specifier(const char **fmt, int *written, va_list *args)
{
	bool	success;

	if (**fmt == 'c')
		success = format_char(written, va_arg(*args, int));
	else if (**fmt == 's')
		success = format_string(written, va_arg(*args, char *));
	else if (**fmt == 'p')
		success = format_pointer(written, va_arg(*args, void *));
	else if (**fmt == 'd' || **fmt == 'i')
		success = format_signed(written, va_arg(*args, int), BASE_DEC);
	else if (**fmt == 'u')
		success = format_unsigned(written, va_arg(*args, unsigned int),
				BASE_DEC);
	else if (**fmt == 'x')
		success = format_unsigned(written, va_arg(*args, unsigned int),
				BASE_HEXL);
	else if (**fmt == 'X')
		success = format_unsigned(written, va_arg(*args, unsigned int),
				BASE_HEXU);
	else if (**fmt == '%')
		success = format_char(written, '%');
	else
		return (false);
	(*fmt)++;
	return (success);
}

static bool	print_until_specifier(const char **fmt, int *written)
{
	size_t	len;

	len = 0;
	while ((*fmt)[len] && (*fmt)[len] != '%')
		len++;
	if (!check_write(written, *fmt, len))
		return (false);
	*fmt += len;
	return (true);
}

int	ft_printf(const char *fmt, ...)
{
	va_list	args;
	bool	success;
	int		written;

	va_start(args, fmt);
	written = 0;
	while (*fmt)
	{
		if (*fmt == '%')
		{
			fmt++;
			success = handle_specifier(&fmt, &written, &args);
		}
		else
			success = print_until_specifier(&fmt, &written);
		if (!success)
			return (-1);
	}
	va_end(args);
	return (written);
}
