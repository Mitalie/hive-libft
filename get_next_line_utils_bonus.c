/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 13:21:26 by amakinen          #+#    #+#             */
/*   Updated: 2024/05/16 14:40:36 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <stdlib.h>
#include <stdint.h>

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

char	*bufs_to_str(const char *b1, size_t l1, const char *b2, size_t l2)
{
	char	*str;

	if (l2 == SIZE_MAX || l1 > SIZE_MAX - 1 - l2)
		return (0);
	str = malloc(l1 + l2 + 1);
	if (!str)
		return (0);
	ft_memcpy(str, b1, l1);
	ft_memcpy(str + l1, b2, l2);
	str[l1 + l2] = 0;
	return (str);
}

void	*cleanup(t_linebuf *line, t_readbuf *readbuf)
{
	free(line->buf);
	free(readbuf->buf);
	readbuf->buf = 0;
	readbuf->len = 0;
	return (0);
}
