/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testfw_strmanip.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 15:49:05 by amakinen          #+#    #+#             */
/*   Updated: 2024/04/25 18:01:09 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "testfw.h"
#include "libft.h"
#include <stdlib.h>
#include <string.h>

static void	check_str(char const *fn, char const *str, char const *match)
{
	if (match && !str)
		TEST_FAIL("%s returned null pointer, expected %s\n", fn, match);
	else if (str && !match)
		TEST_FAIL("%s returned %s, expected null pointer\n", fn, str);
	else if (str && strcmp(str, match))
		TEST_FAIL("%s returned wrong string \"%s\", expected \"%s\"\n",
			fn, str, match);
}

#define CHECK_SUBSTR(s, i, l, match) \
do { \
	char *sub = ft_substr(s, i, l); \
	check_str("ft_substr(\"" s "\", " #i ", " #l ")", sub, match); \
	free(sub); \
} while (0)

REGISTER_TEST(ft_substr);

static void	test_ft_substr(void)
{
	CHECK_SUBSTR("abc", 0, 0, "");
	CHECK_SUBSTR("abc", 0, 2, "ab");
	CHECK_SUBSTR("abc", 0, 4, "abc");
	CHECK_SUBSTR("abc", 2, 3, "c");
	CHECK_SUBSTR("abc", 3, 3, "");
	CHECK_SUBSTR("abc", 4, 3, "");
}

#define CHECK_STRJOIN(s1, s2, match) \
do { \
	char *joined = ft_strjoin(s1, s2); \
	check_str("ft_strjoin(\"" s1 "\", \"" s2 "\")", joined, match); \
	free (joined); \
} while (0)

REGISTER_TEST(ft_strjoin);

static void	test_ft_strjoin(void)
{
	CHECK_STRJOIN("", "", "");
	CHECK_STRJOIN("abc", "", "abc");
	CHECK_STRJOIN("", "def", "def");
	CHECK_STRJOIN("abc", "def", "abcdef");
}

#define CHECK_STRTRIM(s, set, match) \
do { \
	char *trimmed = ft_strtrim(s, set); \
	check_str("ft_strtrim(\"" s "\", \"" set "\")", trimmed, match); \
	free (trimmed); \
} while (0)

REGISTER_TEST(ft_strtrim);

static void	test_ft_strtrim(void)
{
	CHECK_STRTRIM("", "", "");
	CHECK_STRTRIM("abcd", "", "abcd");
	CHECK_STRTRIM("abcd", "ab", "cd");
	CHECK_STRTRIM("abcd", "ba", "cd");
	CHECK_STRTRIM("abcd", "cd", "ab");
	CHECK_STRTRIM("abcd", "ad", "bc");
	CHECK_STRTRIM("abcd", "ac", "bcd");
	CHECK_STRTRIM("abcd", "acccc", "bcd");
	CHECK_STRTRIM("abcd", "fabcde", "");
	CHECK_STRTRIM("abcd", "xyzbcghi", "abcd");
}

#define CHECK_ITOA(n) \
do { \
	char *str = ft_itoa(n); \
	check_str("ft_itoa(" #n ")", str, #n);\
	free (str); \
} while (0)

REGISTER_TEST(ft_itoa);

static void	test_ft_itoa(void)
{
	CHECK_ITOA(2147483647);
	CHECK_ITOA(2147483646);
	CHECK_ITOA(999);
	CHECK_ITOA(1);
	CHECK_ITOA(0);
	CHECK_ITOA(-1);
	CHECK_ITOA(-999);
	CHECK_ITOA(-2147483647);
	CHECK_ITOA(-2147483648);
}
