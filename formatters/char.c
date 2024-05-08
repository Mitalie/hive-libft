/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 16:27:16 by amakinen          #+#    #+#             */
/*   Updated: 2024/05/08 11:21:25 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internal.h"

bool	format_c(t_printf_state *s, t_specifier *spec)
{
	char	c;

	(void)spec;
	c = va_arg(s->args, int);
	return (write_simple(s, &c, 1));
}

bool	format_percent(t_printf_state *s, t_specifier *spec)
{
	char	c;

	(void)spec;
	c = '%';
	return (write_simple(s, &c, 1));
}
