/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specifier.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 10:35:26 by amakinen          #+#    #+#             */
/*   Updated: 2024/05/17 12:00:18 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal.h"

bool	handle_specifier(t_printf_state *s)
{
	char		conv;

	conv = *s->fmt++;
	if (conv == 'c')
		return (format_c(s));
	else if (conv == 's')
		return (format_s(s));
	else if (conv == 'p')
		return (format_p(s));
	else if (conv == 'd' || conv == 'i')
		return (format_d(s));
	else if (conv == 'u')
		return (format_u(s));
	else if (conv == 'x')
		return (format_x(s));
	else if (conv == 'X')
		return (format_x_upper(s));
	else if (conv == '%')
		return (format_percent(s));
	s->fmt--;
	return (true);
}
