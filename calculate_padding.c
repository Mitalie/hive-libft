/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_padding.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 13:02:07 by amakinen          #+#    #+#             */
/*   Updated: 2024/05/08 13:41:29 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internal.h"

bool	calculate_number_padding(t_specifier *spec, t_num_pad *p,
			size_t digits, size_t prefix)
{
	*p = (t_num_pad){0};
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
