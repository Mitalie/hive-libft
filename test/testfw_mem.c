/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testfw_mem.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 17:53:26 by amakinen          #+#    #+#             */
/*   Updated: 2024/04/25 16:18:58 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "testfw.h"
#include "libft.h"
#include <string.h>
#include <strings.h>

REGISTER_TEST(ft_memset);

static void	test_ft_memset(void)
{
	char	buf[20];
	char	*ret;

	bzero(buf, 20);
	ret = ft_memset(buf + 5, 'a', 10);
	if (ret != buf + 5)
		TEST_FAIL("Sub-buffer ft_memset returned wrong pointer\n");
	if (memcmp(buf, "\0\0\0\0\0aaaaaaaaaa\0\0\0\0\0", 20))
		TEST_FAIL("Sub-buffer ft_memset didn't match stdlib\n");
	ret = ft_memset(buf, 'b', 20);
	if (ret != buf)
		TEST_FAIL("Full buffer ft_memset returned wrong pointer\n");
	if (memcmp(buf, "bbbbbbbbbbbbbbbbbbbb", 20))
		TEST_FAIL("Full buffer ft_memset didn't match stdlib\n");
}

REGISTER_TEST(ft_bzero);

static void	test_ft_bzero(void)
{
	char	buf[20];

	memset(buf, 'a', 20);
	ft_bzero(buf + 5, 10);
	if (memcmp(buf, "aaaaa\0\0\0\0\0\0\0\0\0\0aaaaa", 20))
		TEST_FAIL("Sub-buffer ft_bzero didn't match expected\n");
	ft_bzero(buf, 20);
	if (memcmp(buf, "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0", 20))
		TEST_FAIL("Full buffer ft_bzero didn't match expected\n");
}

REGISTER_TEST(ft_memcpy);

static void	test_ft_memcpy(void)
{
	char	buf[20];
	void	*ret;

	memcpy(buf, "12345678901234567890", 20);
	ret = ft_memcpy(buf + 5, "ABCDEFGHIJKLMNOPQRST", 10);
	if (ret != buf + 5)
		TEST_FAIL("Sub-buffer ft_memcpy returned wrong pointer\n");
	if (memcmp(buf, "12345ABCDEFGHIJ67890", 20))
		TEST_FAIL("Sub-buffer ft_memcpy didn't match expected data\n");
	ret = ft_memcpy(buf, "abcdefghijklmnopqrst", 20);
	if (ret != buf)
		TEST_FAIL("Full buffer ft_memcpy returned wrong pointer\n");
	if (memcmp(buf, "abcdefghijklmnopqrst", 20))
		TEST_FAIL("Full buffer ft_memcpy didn't match expected data\n");
}

REGISTER_TEST(ft_memmove);

static void	test_ft_memmove(void)
{
	char	buf[20];
	char	*ret;

	memcpy(buf, "ABCDEFGHIJKLMNOPQRST", 20);
	ret = ft_memmove(buf, buf + 5, 15);
	if (ret != buf)
		TEST_FAIL("Downwards ft_memmove returned wrong pointer\n");
	if (memcmp(buf, "FGHIJKLMNOPQRSTPQRST", 20))
		TEST_FAIL("Downwards ft_memmove didn't match stdlib\n");
	memcpy(buf, "abcdefghijklmnopqrst", 20);
	ret = ft_memmove(buf + 5, buf, 15);
	if (ret != buf + 5)
		TEST_FAIL("Upwards ft_memmove returned wrong pointer\n");
	if (memcmp(buf, "abcdeabcdefghijklmno", 20))
		TEST_FAIL("Upwards ft_memmove didn't match stdlib\n");
}
