/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 11:28:27 by amakinen          #+#    #+#             */
/*   Updated: 2024/05/06 16:13:37 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <limits.h>
#include <stdarg.h>
#include <stdbool.h>
#include <unistd.h>

static bool	handle_specifier(const char **fmt, int *written, va_list *args)
{
	(void)written;
	(void)args;
	(*fmt)++;
	return (false);
}

static bool	print_until_specifier(const char **fmt, int *written)
{
	size_t	len;

	len = 0;
	while ((*fmt)[len] && (*fmt)[len] != '%')
		len++;
	if (len > (unsigned)INT_MAX - *written)
		return (false);
	if (write(STDOUT_FILENO, *fmt, len) < 0)
		return (false);
	*fmt += len;
	*written += len;
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
			success = handle_specifier(&fmt, &written, &args);
		else
			success = print_until_specifier(&fmt, &written);
		if (!success)
			return (-1);
	}
	va_end(args);
	return (written);
}
