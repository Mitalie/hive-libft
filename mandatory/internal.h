/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   internal.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 16:21:32 by amakinen          #+#    #+#             */
/*   Updated: 2024/05/17 11:59:23 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERNAL_H
# define INTERNAL_H

# include "internal_shared.h"

bool	format_c(t_printf_state *s);
bool	format_s(t_printf_state *s);
bool	format_p(t_printf_state *s);
bool	format_d(t_printf_state *s);
bool	format_u(t_printf_state *s);
bool	format_x(t_printf_state *s);
bool	format_x_upper(t_printf_state *s);
bool	format_percent(t_printf_state *s);

#endif
