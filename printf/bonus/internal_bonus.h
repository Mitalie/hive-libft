/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   internal_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 16:21:32 by amakinen          #+#    #+#             */
/*   Updated: 2024/05/17 11:43:27 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERNAL_BONUS_H
# define INTERNAL_BONUS_H

# include "internal_shared.h"

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

bool	write_padded(t_printf_state *s, t_specifier *spec,
			const void *data, size_t len);
bool	write_number(t_printf_state *s, t_specifier *spec, t_number n);

bool	format_c(t_printf_state *s, t_specifier *spec);
bool	format_s(t_printf_state *s, t_specifier *spec);
bool	format_p(t_printf_state *s, t_specifier *spec);
bool	format_d(t_printf_state *s, t_specifier *spec);
bool	format_u(t_printf_state *s, t_specifier *spec);
bool	format_x(t_printf_state *s, t_specifier *spec);
bool	format_x_upper(t_printf_state *s, t_specifier *spec);
bool	format_percent(t_printf_state *s, t_specifier *spec);

#endif
