/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   writers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 18:03:41 by amakinen          #+#    #+#             */
/*   Updated: 2024/05/17 11:34:25 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internal.h"
#include <limits.h>
#include "libft.h"

static bool	write_char_repeat(int fd, char c, size_t n)
{
	char	buf[64];

	ft_memset(buf, c, sizeof(buf));
	while (n > sizeof(buf))
	{
		if (!write_all(fd, buf, sizeof(buf)))
			return (false);
		n -= sizeof(buf);
	}
	return (write_all(fd, buf, n));
}

bool	write_padded(t_printf_state *s, t_specifier *spec,
			const void *data, size_t len)
{
	size_t	pad_len;

	pad_len = 0;
	if (len < spec->width)
		pad_len = spec->width - len;
	if (len + pad_len > (unsigned)INT_MAX - s->written)
		return (false);
	s->written += len + pad_len;
	if (spec->pad_mode == PAD_BLANK && !write_char_repeat(s->fd, ' ', pad_len))
		return (false);
	if (spec->pad_mode == PAD_ZERO && !write_char_repeat(s->fd, '0', pad_len))
		return (false);
	if (!write_all(s->fd, data, len))
		return (false);
	if (spec->pad_mode == PAD_RIGHT && !write_char_repeat(s->fd, ' ', pad_len))
		return (false);
	return (true);
}

static bool	calculate_number_padding(t_specifier *spec, t_num_pad *p,
			size_t digits, size_t prefix)
{
	p->left = 0;
	p->zeroes = 0;
	p->right = 0;
	p->total = digits;
	if (spec->use_precision && p->total < spec->precision)
	{
		p->zeroes = spec->precision - p->total;
		p->total = spec->precision;
	}
	if (prefix > SIZE_MAX - p->total)
		return (false);
	p->total += prefix;
	if (p->total < spec->width)
	{
		if (!spec->use_precision && spec->pad_mode == PAD_ZERO)
			p->zeroes = spec->width - p->total;
		else if (spec->pad_mode == PAD_RIGHT)
			p->right = spec->width - p->total;
		else
			p->left = spec->width - p->total;
		p->total = spec->width;
	}
	return (true);
}

bool	write_number(t_printf_state *s, t_specifier *spec, t_number n)
{
	t_num_pad	pad;

	if (!calculate_number_padding(spec, &pad, n.digits_len, n.prefix_len))
		return (false);
	if (pad.total > (unsigned)INT_MAX - s->written)
		return (false);
	s->written += pad.total;
	if (!write_char_repeat(s->fd, ' ', pad.left))
		return (false);
	if (!write_all(s->fd, n.prefix, n.prefix_len))
		return (false);
	if (!write_char_repeat(s->fd, '0', pad.zeroes))
		return (false);
	if (!write_all(s->fd, n.digits, n.digits_len))
		return (false);
	if (!write_char_repeat(s->fd, ' ', pad.right))
		return (false);
	return (true);
}
