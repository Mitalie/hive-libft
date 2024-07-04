/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_string_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 16:45:56 by amakinen          #+#    #+#             */
/*   Updated: 2024/07/03 13:39:52 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal_bonus.h"
#include "libft.h"

bool	format_s(t_printf_state *s, t_specifier *spec)
{
	size_t		len;
	const char	*str;

	str = va_arg(s->args, const char *);
	if (IS_LINUX && !str && spec->use_precision && spec->precision < 6)
		str = "";
	if (!str)
		str = "(null)";
	len = ft_strlen(str);
	if (spec->use_precision && len > spec->precision)
		len = spec->precision;
	return (write_padded(s, spec, str, len));
}
