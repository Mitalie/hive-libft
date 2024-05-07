/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_internal.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 16:21:32 by amakinen          #+#    #+#             */
/*   Updated: 2024/05/07 12:13:23 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_INTERNAL_H
# define FT_PRINTF_INTERNAL_H

# include <stdarg.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdint.h>

typedef struct s_printf_state
{
	const char	*fmt;
	va_list		args;
	int			written;
}	t_printf_state;

int		utoa_arr_base(unsigned int n, char *arr, char *base, unsigned int nb);
int		ptoa_arr_base(uintptr_t n, char *arr, char *base, uintptr_t nb);

bool	check_write(t_printf_state *s, const void *data, size_t len);

bool	format_c(t_printf_state *s);
bool	format_s(t_printf_state *s);
bool	format_p(t_printf_state *s);
bool	format_d(t_printf_state *s);
bool	format_u(t_printf_state *s);
bool	format_x(t_printf_state *s);
bool	format_x_upper(t_printf_state *s);
bool	format_percent(t_printf_state *s);

#endif
