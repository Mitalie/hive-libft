/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   num_str_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 11:10:41 by amakinen          #+#    #+#             */
/*   Updated: 2024/05/07 15:30:59 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internal.h"

size_t	utoa_arr_base(unsigned int n, char *arr, char *base, unsigned int nb)
{
	int	len;

	len = 0;
	if (n >= nb)
		len += utoa_arr_base(n / nb, arr, base, nb);
	arr[len] = base[n % nb];
	return (len + 1);
}

size_t	ptoa_arr_base(uintptr_t n, char *arr, char *base, uintptr_t nb)
{
	size_t	len;

	len = 0;
	if (n >= nb)
		len += ptoa_arr_base(n / nb, arr, base, nb);
	arr[len] = base[n % nb];
	return (len + 1);
}
