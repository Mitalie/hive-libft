/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_internal.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 16:21:32 by amakinen          #+#    #+#             */
/*   Updated: 2024/05/06 18:07:26 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_INTERNAL_H
# define FT_PRINTF_INTERNAL_H

# include <stdbool.h>
# include <stddef.h>

bool	check_write(int *written, const void *data, size_t len);

bool	format_char(int *written, char c);
bool	format_string(int *written, char *s);
bool	format_pointer(int *written, void *p);
bool	format_unsigned(int *written, unsigned int n, char *base);
bool	format_signed(int *written, int n, char *base);

#endif
