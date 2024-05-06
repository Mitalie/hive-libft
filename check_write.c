/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_write.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 18:03:41 by amakinen          #+#    #+#             */
/*   Updated: 2024/05/06 18:06:55 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internal.h"
#include <limits.h>
#include <unistd.h>

bool	check_write(int *written, const void *data, size_t len)
{
	if (len > (unsigned)INT_MAX - *written)
		return (false);
	*written += len;
	return (write(STDOUT_FILENO, data, len) >= 0);
}
