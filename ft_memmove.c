/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 19:03:02 by amakinen          #+#    #+#             */
/*   Updated: 2024/04/16 19:25:11 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	idx;

	if (dst > src)
	{
		idx = len;
		while (idx--)
			((unsigned char *)dst)[idx] = ((unsigned char *)src)[idx];
	}
	else
	{
		idx = 0;
		while (idx < len)
		{
			((unsigned char *)dst)[idx] = ((unsigned char *)src)[idx];
			idx++;
		}
	}
	return (dst);
}
