/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   internal.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 16:21:32 by amakinen          #+#    #+#             */
/*   Updated: 2024/07/04 15:42:22 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERNAL_H
# define INTERNAL_H

# include <stdarg.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdint.h>

/*
	Standard printf behaves differently on Linux than on Mac OS X, and we're
	supposed to match whatever the system one does. Strictly speaking we should
	probably test for glibc, but just assume Linux == glibc for now.
*/
# ifdef __linux__
#  define IS_LINUX 1
# else
#  define IS_LINUX 0
# endif

typedef struct s_printf_state
{
	int			fd;
	const char	*fmt;
	va_list		args;
	int			written;
}	t_printf_state;

typedef enum e_pad_mode
{
	PAD_BLANK,
	PAD_ZERO,
	PAD_RIGHT,
}	t_pad_mode;

typedef enum e_sign_mode
{
	SIGN_MINUS_ONLY,
	SIGN_BLANK,
	SIGN_PLUS,
}	t_sign_mode;

typedef struct s_specifier
{
	bool			alternate;
	t_pad_mode		pad_mode;
	t_sign_mode		sign_mode;
	unsigned int	width;
	unsigned int	precision;
	bool			use_precision;
}	t_specifier;

typedef struct s_number
{
	const void	*digits;
	size_t		digits_len;
	const void	*prefix;
	size_t		prefix_len;
}	t_number;

typedef struct s_num_pad
{
	size_t	left;
	size_t	zeroes;
	size_t	right;
	size_t	total;
}	t_num_pad;

size_t	utoa_arr_base(unsigned int n, char *arr, char *base, unsigned int nb);
size_t	ptoa_arr_base(uintptr_t n, char *arr, char *base, uintptr_t nb);
bool	write_all(int fd, const void *buf, size_t len);
bool	write_simple(t_printf_state *s, const void *data, size_t len);
bool	write_padded(t_printf_state *s, t_specifier *spec,
			const void *data, size_t len);
bool	write_number(t_printf_state *s, t_specifier *spec, t_number n);

bool	handle_specifier(t_printf_state *s);
bool	format_c(t_printf_state *s, t_specifier *spec);
bool	format_s(t_printf_state *s, t_specifier *spec);
bool	format_p(t_printf_state *s, t_specifier *spec);
bool	format_d(t_printf_state *s, t_specifier *spec);
bool	format_u(t_printf_state *s, t_specifier *spec);
bool	format_x(t_printf_state *s, t_specifier *spec);
bool	format_x_upper(t_printf_state *s, t_specifier *spec);
bool	format_percent(t_printf_state *s, t_specifier *spec);

#endif
