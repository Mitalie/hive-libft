/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_specifier.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 10:35:26 by amakinen          #+#    #+#             */
/*   Updated: 2024/05/07 17:37:00 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internal.h"

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
		else
			return ;
		s->fmt++;
		c = *s->fmt;
	}
}

static bool	parse_spec_width(t_printf_state *s, t_specifier *spec)
{
	return (parse_uint(&s->fmt, &spec->width));
}

static bool	parse_spec_precision(t_printf_state *s, t_specifier *spec)
{
	if (*s->fmt == '.')
	{
		spec->use_precision = true;
		s->fmt++;
		return (parse_uint(&s->fmt, &spec->precision));
	}
	return (true);
}

bool	parse_specifier(t_printf_state *s, t_specifier *spec)
{
	spec->alternate = false;
	spec->pad_mode = PAD_BLANK;
	spec->sign_mode = SIGN_MINUS_ONLY;
	spec->width = 0;
	spec->precision = 0;
	spec->use_precision = false;
	parse_spec_flags(s, spec);
	if (!parse_spec_width(s, spec))
		return (false);
	return (parse_spec_precision(s, spec));
}
