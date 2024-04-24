/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testfw_mem.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 17:53:26 by amakinen          #+#    #+#             */
/*   Updated: 2024/04/24 15:47:09 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "testfw.h"
#include "libft.h"
#include <string.h>
#include <strings.h>
#include <stdio.h>

TEST(ft_memset)
{
	char	buf1[20];
	char	buf2[20];
	bzero(buf1, 20);
	bzero(buf2, 20);
	ft_memset(buf1 + 5, 0x55, 10);
	memset(buf2 + 5, 0x55, 10);
	if (memcmp(buf1, buf2, 20))
		TEST_FAIL("Sub-buffer ft_memset didn't match stdlib\n");
	ft_memset(buf1, 0xaa, 20);
	memset(buf2, 0xaa, 20);
	if (memcmp(buf1, buf2, 20))
		TEST_FAIL("Full buffer ft_memset didn't match stdlib\n");
}

TEST(ft_bzero)
{
	char	buf1[20];
	char	buf2[20];

	memset(buf1, 0xcc, 20);
	memset(buf2, 0xcc, 20);
	ft_bzero(buf1 + 5, 10);
	bzero(buf2 + 5, 10);
	if (memcmp(buf1, buf2, 20))
		TEST_FAIL("Sub-buffer ft_bzero didn't match stdlib\n");
	ft_bzero(buf1, 20);
	bzero(buf2, 20);
	if (memcmp(buf1, buf2, 20))
		TEST_FAIL("Full buffer ft_bzero didn't match stdlib\n");
}

TEST(ft_memcpy)
{
	char	buf1[20];
	char	buf2[20];

	memcpy(buf1, "ABCDEFGHIJKLMNOPQRST", 20);
	memcpy(buf2, "ABCDEFGHIJKLMNOPQRST", 20);
	ft_memcpy(buf1 + 5, "abcdefghijklmnopqrst", 10);
	memcpy(buf2 + 5, "abcdefghijklmnopqrst", 10);
	if (memcmp(buf1, buf2, 20))
		TEST_FAIL("Sub-buffer ft_memcpy didn't match stdlib\n");
	ft_memcpy(buf1, "abcdefghijklmnopqrst", 20);
	memcpy(buf2, "abcdefghijklmnopqrst", 20);
	if (memcmp(buf1, buf2, 20))
		TEST_FAIL("Full buffer ft_memcpy didn't match stdlib\n");
}

TEST(ft_memmove)
{
	char	buf1[20];
	char	buf2[20];

	memcpy(buf1, "ABCDEFGHIJKLMNOPQRST", 20);
	memcpy(buf2, "ABCDEFGHIJKLMNOPQRST", 20);
	ft_memmove(buf1, buf1 + 5, 15);
	memmove(buf2, buf2 + 5, 15);
	if (memcmp(buf1, buf2, 20))
		TEST_FAIL("Downwards ft_memmove didn't match stdlib\n");
	memcpy(buf1, "ABCDEFGHIJKLMNOPQRST", 20);
	memcpy(buf2, "ABCDEFGHIJKLMNOPQRST", 20);
	ft_memmove(buf1 + 5, buf1, 15);
	memmove(buf2 + 5, buf2, 15);
	if (memcmp(buf1, buf2, 20))
		TEST_FAIL("Upwards ft_memmove didn't match stdlib\n");
}
