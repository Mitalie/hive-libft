/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specifier.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 10:35:26 by amakinen          #+#    #+#             */
/*   Updated: 2024/05/17 11:52:16 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal.h"
#include <limits.h>
#include "libft.h"

static void	parse_spec_flags(t_printf_state *s, t_specifier *spec)
{
	char	c;

	c = *s->fmt;
	while (c)
	{
		if (c == '#')
			spec->alternate = true;
		else if (c == '0' && spec->pad_mode != PAD_RIGHT)
			spec->pad_mode = PAD_ZERO;
		else if (c == '-')
			spec->pad_mode = PAD_RIGHT;
		else if (c == ' ' && spec->sign_mode != SIGN_PLUS)
			spec->sign_mode = SIGN_BLANK;
		else if (c == '+')
			spec->sign_mode = SIGN_PLUS;
		else if (c == '0' || c == ' ')
			;
		else
			return ;
		s->fmt++;
		c = *s->fmt;
	}
}

static bool	parse_uint(const char **str, unsigned int *value)
{
	unsigned int	v;
	unsigned int	digit;

	v = 0;
	while (ft_isdigit(**str))
	{
		digit = **str - '0';
		if (v > (UINT_MAX - digit) / 10)
			return (false);
		v = 10 * v + digit;
		(*str)++;
	}
	*value = v;
	return (true);
}

static bool	parse_specifier(t_printf_state *s, t_specifier *spec)
{
	spec->alternate = false;
	spec->pad_mode = PAD_BLANK;
	spec->sign_mode = SIGN_MINUS_ONLY;
	spec->width = 0;
	spec->precision = 0;
	spec->use_precision = false;
	parse_spec_flags(s, spec);
	if (!parse_uint(&s->fmt, &spec->width))
		return (false);
	if (*s->fmt == '.')
	{
		spec->use_precision = true;
		s->fmt++;
		return (parse_uint(&s->fmt, &spec->precision));
	}
	return (true);
}

bool	handle_specifier(t_printf_state *s)
{
	t_specifier	spec;
	char		conv;

	if (!parse_specifier(s, &spec))
		return (false);
	conv = *s->fmt++;
	if (conv == 'c')
		return (format_c(s, &spec));
	else if (conv == 's')
		return (format_s(s, &spec));
	else if (conv == 'p')
		return (format_p(s, &spec));
	else if (conv == 'd' || conv == 'i')
		return (format_d(s, &spec));
	else if (conv == 'u')
		return (format_u(s, &spec));
	else if (conv == 'x')
		return (format_x(s, &spec));
	else if (conv == 'X')
		return (format_x_upper(s, &spec));
	else if (conv == '%')
		return (format_percent(s, &spec));
	s->fmt--;
	return (true);
}
