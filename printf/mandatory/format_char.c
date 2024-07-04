/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 16:27:16 by amakinen          #+#    #+#             */
/*   Updated: 2024/05/17 12:01:58 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal.h"

bool	format_c(t_printf_state *s)
{
	char	c;

	c = va_arg(s->args, int);
	return (write_simple(s, &c, 1));
}

bool	format_percent(t_printf_state *s)
{
	char	c;

	c = '%';
	return (write_simple(s, &c, 1));
}
