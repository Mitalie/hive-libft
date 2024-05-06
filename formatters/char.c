/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 16:27:16 by amakinen          #+#    #+#             */
/*   Updated: 2024/05/06 19:10:24 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internal.h"

static bool	format_char_value(t_printf_state *s, char c)
{
	if (!check_write(s, &c, 1))
		return (false);
	return (true);
}

bool	format_char(t_printf_state *s)
{
	return (format_char_value(s, va_arg(s->args, int)));
}

bool	format_percent(t_printf_state *s)
{
	return (format_char_value(s, '%'));
}
