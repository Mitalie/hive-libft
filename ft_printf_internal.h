/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_internal.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 16:21:32 by amakinen          #+#    #+#             */
/*   Updated: 2024/05/06 19:10:52 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_INTERNAL_H
# define FT_PRINTF_INTERNAL_H

# include <stdarg.h>
# include <stdbool.h>
# include <stddef.h>

typedef struct s_printf_state
{
	const char	*fmt;
	va_list		args;
	int			written;
}	t_printf_state;

bool	check_write(t_printf_state *s, const void *data, size_t len);

bool	format_char(t_printf_state *s);
bool	format_string(t_printf_state *s);
bool	format_pointer(t_printf_state *s);
bool	format_unsigned(t_printf_state *s, char *base);
bool	format_signed(t_printf_state *s, char *base);
bool	format_percent(t_printf_state *s);

#endif
