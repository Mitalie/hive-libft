/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 16:45:56 by amakinen          #+#    #+#             */
/*   Updated: 2024/05/08 12:31:43 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internal.h"
#include "libft.h"

bool	format_s(t_printf_state *s, t_specifier *spec)
{
	size_t		len;
	const char	*str;

	str = va_arg(s->args, const char *);
	if (!str)
		str = "(null)";
	len = ft_strlen(str);
	if (spec->use_precision && len > spec->precision)
		len = spec->precision;
	return (write_padded(s, spec, str, len));
}
