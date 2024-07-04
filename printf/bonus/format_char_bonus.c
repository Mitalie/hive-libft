/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_char_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 16:27:16 by amakinen          #+#    #+#             */
/*   Updated: 2024/07/03 13:10:25 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal_bonus.h"

bool	format_c(t_printf_state *s, t_specifier *spec)
{
	char	c;

	c = va_arg(s->args, int);
	return (write_padded(s, spec, &c, 1));
}

bool	format_percent(t_printf_state *s, t_specifier *spec)
{
	char	c;

	c = '%';
	if (IS_LINUX)
		return (write_simple(s, &c, 1));
	return (write_padded(s, spec, &c, 1));
}
