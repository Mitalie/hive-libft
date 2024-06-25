/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testfw_alloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 15:17:06 by amakinen          #+#    #+#             */
/*   Updated: 2024/05/02 12:50:34 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "testfw.h"
#include "libft.h"
#include <stdlib.h>
#include <string.h>

#define COUNT 5000
#define SIZE 4000
// HUGE = 2^34
#define HUGE 17179869184ul

REGISTER_TEST(ft_calloc);

/*
	Expect crash if full size of returned memory is not writable.
	Zero size or count shouldn't crash, but it is implementation defined whether
	it returns a NULL pointer or a valid unique pointer. On macOS Mojave the
	libc calloc returns a valid pointer, and Moulinette and some test kits
	require ft_calloc does too.
*/
static void	test_ft_calloc(void)
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
		buf[idx++] = 1;
	}
	free(buf);
	buf = ft_calloc(HUGE, HUGE);
	if (buf)
		TEST_FAIL("ft_calloc(%ld, %ld) returned a non-null pointer"
			" (impossibly large alloc)\n", HUGE, HUGE);
	free(buf);
	buf = ft_calloc(0, 1);
	if (!buf)
		TEST_FAIL("ft_calloc(0, 1) returned a null pointer\n");
	free(buf);
	buf = ft_calloc(1, 0);
	if (!buf)
		TEST_FAIL("ft_calloc(1, 0) returned a null pointer\n");
	free(buf);
	buf = ft_calloc(0, 0);
	if (!buf)
		TEST_FAIL("ft_calloc(0, 0) returned a null pointer\n");
	free(buf);
}

REGISTER_TEST(ft_strdup);

// Expect crash if full size of returned memory is not writable
static void	test_ft_strdup(void)
{
	const char	*str;
	char		*dup;
	int			idx;

	idx = 0;
	str = "abcdef";
	dup = ft_strdup(str);
	if (dup == str)
		TEST_FAIL("ft_strdup returned the original address\n");
	if (!dup)
		TEST_FAIL("ft_strdup returned a null pointer\n");
	if (dup && strcmp(str, dup))
		TEST_FAIL("ft_strdup returned wrong string\n");
	while (dup && idx <= 6)
		dup[idx++] = 0;
	free(dup);
}
