/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 15:46:24 by amakinen          #+#    #+#             */
/*   Updated: 2024/05/15 10:27:28 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	idx;

	if (dst == src)
		return (dst);
	idx = 0;
	while (idx < n)
	{
		((unsigned char *)dst)[idx] = ((unsigned char *)src)[idx];
		idx++;
	}
	return (dst);
}

void	*ft_reallocf(void *old_alloc, size_t new_size, size_t old_data_len)
{
	void	*new_alloc;

	new_alloc = malloc(new_size);
	if (old_data_len > new_size)
		old_data_len = new_size;
	if (new_alloc)
		ft_memcpy(new_alloc, old_alloc, old_data_len);
	free(old_alloc);
	return (new_alloc);
}
