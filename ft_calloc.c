/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 12:23:22 by amakinen          #+#    #+#             */
/*   Updated: 2024/04/30 13:11:02 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <stdint.h>

/*
	C allows implementations to decide whether to return a NULL pointer or a
	unique freeable pointer for zero size allocations. The libft assignment
	requires matching the libc function behaviour, so we avoid filtering zero
	sizes with an early return and pass them on to libc malloc.

	Some libft testers explicitly require non-NULL pointers, which this
	implementation would fail if malloc returns NULL, but if that happens it's
	likely libc calloc would also return NULL and therefore the test is wrong.
*/

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	if (size && count > SIZE_MAX / size)
		return (0);
	ptr = malloc(count * size);
	if (ptr)
		ft_bzero(ptr, count * size);
	return (ptr);
}
