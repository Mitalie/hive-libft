/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testfw_search.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 16:05:44 by amakinen          #+#    #+#             */
/*   Updated: 2024/04/24 16:35:36 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "testfw.h"
#include "libft.h"
#include <string.h>
#include <stdio.h>

#define MATCHCHR(fn, s, c) \
	ft_r = ft_##fn(s, c); \
	std_r = fn(s, c); \
	if (ft_r != std_r) \
	{ \
		TEST_FAIL("ft_" #fn "(\"%s\", '%c'<%d>) failed: " \
			"ft_ returned %p, std returned %p\n", \
			s, c, c, ft_r, std_r); \
	}

#define TESTCHR(n) \
REGISTER_TEST(ft_##n);\
\
static void	test_ft_##n(void)\
{\
	char	*ft_r;\
	char	*std_r;\
\
	MATCHCHR(n, "abc", 'a')\
	MATCHCHR(n, "abc", 'b')\
	MATCHCHR(n, "abc", 'c')\
	MATCHCHR(n, "abc", '\0')\
	MATCHCHR(n, "abc", 'd')\
	MATCHCHR(n, "abc", 'A')\
}

TESTCHR(strchr)
TESTCHR(strrchr)

#define MATCHMEMCHR(s, c, n) \
	ft_r = ft_memchr(s, c, n); \
	std_r = memchr(s, c, n); \
	if (ft_r != std_r) \
	{ \
		TEST_FAIL("ft_memchr(\"%s\", '%c'<%d>, %d) failed: " \
			"ft_ returned %p, std returned %p\n", \
			s, c, c, n, ft_r, std_r); \
	}

REGISTER_TEST(ft_memchr);

static void	test_ft_memchr(void)
{
	char	*ft_r;
	char	*std_r;

	MATCHMEMCHR("abc", 'a', 4)
	MATCHMEMCHR("abc", 'b', 4)
	MATCHMEMCHR("abc", 'c', 4)
	MATCHMEMCHR("abc", '\0', 4)
	MATCHMEMCHR("abc", '\0', 3)
	MATCHMEMCHR("abc", 'd', 4)
	MATCHMEMCHR("abc", 'A', 4)
}

#define MATCHSTRNSTR(haystack, needle, len) \
	std_r = strnstr(haystack, needle, len); \
	ft_r = ft_strnstr(haystack, needle, len); \
	if (ft_r != std_r) \
	{ \
		TEST_FAIL("ft_strnstr(\"%s\", \"%s\", %d) failed: " \
			"ft_ returned %p, std returned %p\n", \
			haystack, needle, len, ft_r, std_r); \
	}

REGISTER_TEST(ft_strnstr);

static void	test_ft_strnstr(void)
{
	char	*ft_r;
	char	*std_r;

	MATCHSTRNSTR("abcd", "abcd", 4)
	MATCHSTRNSTR("abcd", "abcd", 3)
	MATCHSTRNSTR("abcd", "bc", 4)
	MATCHSTRNSTR("abcd", "bc", 3)
	MATCHSTRNSTR("abcd", "bc", 2)
	MATCHSTRNSTR("abcd", "cd", 4)
	MATCHSTRNSTR("abcd", "cd", 3)
	MATCHSTRNSTR("abcd", "a", 5)
	MATCHSTRNSTR("abcd", "a", 1)
	MATCHSTRNSTR("abcd", "a", 0)
	MATCHSTRNSTR("\0abcd", "a", 5)
	MATCHSTRNSTR("abcd", "", 5)
	MATCHSTRNSTR("abcd", "", 1)
	MATCHSTRNSTR("abcd", "", 0)
	MATCHSTRNSTR("abcd", "\0a", 4)
	MATCHSTRNSTR("abcd", "\0a", 1)
	MATCHSTRNSTR("abcd", "\0a", 0)
	MATCHSTRNSTR("abcd", "abcde", 5)
	MATCHSTRNSTR("abcd", "abcde", 4)
	MATCHSTRNSTR("abcd", "abce", 4)
	MATCHSTRNSTR("abcd", "abce", 3)
	MATCHSTRNSTR("abcd", "cb", 4)
	MATCHSTRNSTR((char*)0, "", 1)
	MATCHSTRNSTR((char*)0, "", 0)
}
