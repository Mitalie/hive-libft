/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testfw_alloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 15:17:06 by amakinen          #+#    #+#             */
/*   Updated: 2024/04/23 15:48:08 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "testfw.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define COUNT 5000
#define SIZE 4000
#define HUGE (1l << 34)

TEST(ft_calloc)
{
	char	*buf;
	int		fail;
	int		idx;

	fail = 0;
	idx = 0;
	buf = ft_calloc(COUNT, SIZE);
	if (!buf)
	{
		printf("ft_calloc(%d, %d) returned a null pointer\n", COUNT, SIZE);
		fail = 1;
	}
	while (buf && idx < COUNT * SIZE)
	{
		if (buf[idx])
		{
			printf("ft_calloc did not zero memory at index %d\n", idx);
			fail = 1;
		}
		// Make sure it's writable - expect crash if not
		buf[idx++] = 1;
	}
	free(buf);
	buf = ft_calloc(HUGE, HUGE);
	if (buf)
	{
		printf("ft_calloc(%ld, %ld) returned a non-null pointer"
			" (impossibly large alloc)\n", HUGE, HUGE);
		fail = 1;
	}
	free(buf);
	return (fail);
}

TEST(ft_strdup)
{
	const char	*str;
	char		*dup;
	int			fail;
	int			idx;

	fail = 0;
	idx = 0;
	str = "abcdef";
	dup = ft_strdup(str);
	if (dup == str)
	{
		printf("ft_strdup returned the original address\n");
		fail = 1;
	}
	if (!dup)
	{
		printf("ft_strdup returned a null pointer\n");
		fail = 1;
	}
	if (dup && strcmp(str, dup))
	{
		printf("ft_strdup returned wrong string\n");
		fail = 1;
	}
	free(dup);
	dup = ft_strdup(str);
	while (dup && idx <= 6)
	{
		// Make sure it's writable - expect crash if not
		dup[idx++] = 0;
	}
	return (fail);
}
