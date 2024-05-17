/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   internal_shared.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 11:41:39 by amakinen          #+#    #+#             */
/*   Updated: 2024/05/17 11:42:53 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERNAL_SHARED_H
# define INTERNAL_SHARED_H

# include <stdarg.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdint.h>

typedef struct s_printf_state
{
	int			fd;
	const char	*fmt;
	va_list		args;
	int			written;
}	t_printf_state;

size_t	utoa_arr_base(unsigned int n, char *arr, char *base, unsigned int nb);
size_t	ptoa_arr_base(uintptr_t n, char *arr, char *base, uintptr_t nb);
bool	write_all(int fd, const void *buf, size_t len);
bool	write_simple(t_printf_state *s, const void *data, size_t len);

bool	handle_specifier(t_printf_state *s);

#endif
