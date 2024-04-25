/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testfw_strmanip.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 15:49:05 by amakinen          #+#    #+#             */
/*   Updated: 2024/04/25 16:20:11 by amakinen         ###   ########.fr       */
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

static char	testmap(unsigned int idx, char c)
{
	if (c >= 'a' && c <= 'z')
		c = 'a' + (c - 'a' + idx) % 26;
	else if (c >= 'A' && c <= 'Z')
		c = 'A' + (c - 'A' + idx) % 26;
	return (c);
}

#define CHECK_MAP(s, match) \
do { \
	char *mapped = ft_strmapi(s, testmap); \
	check_str("ft_strmapi(\"" s "\", testmap)", mapped, match); \
	free (mapped); \
} while (0)

REGISTER_TEST(ft_strmapi);

static void	test_ft_strmapi(void)
{
	CHECK_MAP("", "");
	CHECK_MAP("abcdEFGH", "acegIKMO");
}

static void	testtrans(unsigned int idx, char *cp)
{
	char	c;

	c = *cp;
	if (c >= 'a' && c <= 'z')
		c = 'a' + (c - 'a' + idx) % 26;
	else if (c >= 'A' && c <= 'Z')
		c = 'A' + (c - 'A' + idx) % 26;
	*cp = c;
}

#define CHECK_ITER(s, match) \
do { \
	char	buf[sizeof(match)]; \
	strcpy(buf, s); \
	ft_striteri(buf, testtrans); \
	check_str("ft_striteri(\"" s "\", testmap)", buf, match); \
} while (0)

REGISTER_TEST(ft_striteri);

static void	test_ft_striteri(void)
{
	CHECK_ITER("", "");
	CHECK_ITER("abcdEFGH", "acegIKMO");
}

static void	check_strarr(const char *fn, char **arr, char **match)
{
	size_t	idx;

	idx = 0;
	if (!arr)
		TEST_FAIL("%s returned null pointer", fn);
	while (match && (*arr || *match))
	{
		if (!*arr)
			TEST_FAIL("%s: mismatch at idx %zu, "
				"found null pointer, expected \"%s\"\n", fn, idx, *match);
		else if (!*match)
			TEST_FAIL("%s: mismatch at idx %zu, "
				"found \"%s\", expected null pointer\n", fn, idx, *arr);
		else if (strcmp(*arr, *match))
			TEST_FAIL("%s: mismatch at idx %zu, "
				"found \"%s\", expected \"%s\"\n", fn, idx, *arr, *match);
		else
		{
			arr++;
			match++;
			idx++;
			continue ;
		}
		return ;
	}
}

#define CHECK_STRARR(s, c, match) \
do { \
	char **arr = ft_split(s, c); \
	check_strarr("ft_split(\"" s "\", " #c ")", arr, match); \
	char **iter = arr; \
	while (*iter) \
		free(*iter++); \
	free (arr); \
} while (0)

REGISTER_TEST(ft_split);

/* These tests expect empty strings between multiple separatos */
/*
static void	test_ft_split(void)
{
	CHECK_STRARR("", '|', ((char *[]){"", 0}));
	CHECK_STRARR("abc", '|', ((char *[]){"abc", 0}));
	CHECK_STRARR("a|b|c", '|', ((char *[]){"a", "b", "c", 0}));
	CHECK_STRARR("a||b", '|', ((char *[]){"a", "", "b", 0}));
	CHECK_STRARR("|a|||b|", '|', ((char *[]){"", "a", "", "", "b", "", 0}));
}
*/

/* These tests expect empty strings to not be included in the output */
static void	test_ft_split(void)
{
	CHECK_STRARR("", '|', ((char *[]){0}));
	CHECK_STRARR("abc", '|', ((char *[]){"abc", 0}));
	CHECK_STRARR("a|b|c", '|', ((char *[]){"a", "b", "c", 0}));
	CHECK_STRARR("a||b", '|', ((char *[]){"a", "b", 0}));
	CHECK_STRARR("|a|||b|", '|', ((char *[]){"a", "b", 0}));
}
