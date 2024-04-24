/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testfw_alloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 15:17:06 by amakinen          #+#    #+#             */
/*   Updated: 2024/04/24 15:41:29 by amakinen         ###   ########.fr       */
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
	int		idx;

	idx = 0;
	buf = ft_calloc(COUNT, SIZE);
	if (!buf)
		TEST_FAIL("ft_calloc(%d, %d) returned a null pointer\n", COUNT, SIZE);
	while (buf && idx < COUNT * SIZE)
	{
		if (buf[idx])
			TEST_FAIL("ft_calloc did not zero memory at index %d\n", idx);
		// Make sure it's writable - expect crash if not
		buf[idx++] = 1;
	}
	free(buf);
	buf = ft_calloc(HUGE, HUGE);
	if (buf)
	{
		TEST_FAIL("ft_calloc(%ld, %ld) returned a non-null pointer"
			" (impossibly large alloc)\n", HUGE, HUGE);
	}
	free(buf);
}

TEST(ft_strdup)
{
	const char	*str;
	char		*dup;
	int			idx;

	idx = 0;
	str = "abcdef";
	dup = ft_strdup(str);
	if (dup == str)
	{
		TEST_FAIL("ft_strdup returned the original address\n");
	}
	if (!dup)
	{
		TEST_FAIL("ft_strdup returned a null pointer\n");
	}
	if (dup && strcmp(str, dup))
	{
		TEST_FAIL("ft_strdup returned wrong string\n");
	}
	free(dup);
	dup = ft_strdup(str);
	while (dup && idx <= 6)
	{
		// Make sure it's writable - expect crash if not
		dup[idx++] = 0;
	}
}
