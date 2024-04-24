/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testfw_strmanip.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 15:49:05 by amakinen          #+#    #+#             */
/*   Updated: 2024/04/24 11:38:42 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "testfw.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int	check_str(char const *fn, char const *str, char const *match)
{
	if (match && !str)
		printf("%s returned null pointer, expected %s\n", fn, match);
	else if (str && !match)
		printf("%s returned %s, expected null pointer\n", fn, str);
	else if (str && strcmp(str, match))
		printf("%s returned wrong string \"%s\", expected \"%s\"\n",
			fn, str, match);
	else
		return (0);
	return (1);
}

#define CHECK_SUBSTR(s, i, l, match) \
do { \
	char *sub = ft_substr(s, i, l); \
	fail = check_str("ft_substr(\"" s "\", " #i ", " #l ")", sub, match) || fail; \
	free(sub); \
} while (0)

TEST(ft_substr)
{
	int	fail;

	fail = 0;
	CHECK_SUBSTR("abc", 0, 0, "");
	CHECK_SUBSTR("abc", 0, 2, "ab");
	CHECK_SUBSTR("abc", 0, 4, "abc");
	CHECK_SUBSTR("abc", 2, 3, "c");
	CHECK_SUBSTR("abc", 3, 3, "");
	CHECK_SUBSTR("abc", 4, 3, "");
	return (fail);
}

#define CHECK_STRJOIN(s1, s2, match) \
do { \
	char *joined = ft_strjoin(s1, s2); \
	fail = check_str("ft_strjoin(\"" s1 "\", \"" s2 "\")", joined, match) || fail; \
	free (joined); \
} while (0)

TEST(ft_strjoin)
{
	int	fail;

	fail = 0;
	CHECK_STRJOIN("", "", "");
	CHECK_STRJOIN("abc", "", "abc");
	CHECK_STRJOIN("", "def", "def");
	CHECK_STRJOIN("abc", "def", "abcdef");
	return (fail);
}

#define CHECK_STRTRIM(s, set, match) \
do { \
	char *trimmed = ft_strtrim(s, set); \
	fail = check_str("ft_strtrim(\"" s "\", \"" set "\")", trimmed, match) || fail; \
	free (trimmed); \
} while (0)

TEST(ft_strtrim)
{
	int	fail;

	fail = 0;
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
	return (fail);
}

#define CHECK_ITOA(n) \
do { \
	char *str = ft_itoa(n); \
	fail = check_str("ft_itoa(" #n ")", str, #n) || fail;\
	free (str); \
} while (0)

TEST(ft_itoa)
{
	int	fail;

	fail = 0;
	CHECK_ITOA(2147483647);
	CHECK_ITOA(2147483646);
	CHECK_ITOA(999);
	CHECK_ITOA(1);
	CHECK_ITOA(0);
	CHECK_ITOA(-1);
	CHECK_ITOA(-999);
	CHECK_ITOA(-2147483647);
	CHECK_ITOA(-2147483648);
	return (fail);
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
	fail = check_str("ft_strmapi(\"" s "\", testmap)", mapped, match) || fail; \
	free (mapped); \
} while (0)

TEST(ft_strmapi)
{
	int	fail;

	fail = 0;
	CHECK_MAP("", "");
	CHECK_MAP("abcdEFGH", "acegIKMO");
	return (fail);
}

static void	testtrans(unsigned int idx, char *cp)
{
	char c = *cp;
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
	fail = check_str("ft_striteri(\"" s "\", testmap)", buf, match) || fail; \
} while (0)

TEST(ft_striteri)
{
	int		fail;

	fail = 0;
	CHECK_ITER("", "");
	CHECK_ITER("abcdEFGH", "acegIKMO");
	return (fail);
}

static int	check_strarr(const char *fn, char **arr, char **match)
{
	size_t	idx;

	idx = 0;
	if (!arr)
	{
		printf("%s returned null pointer", fn);
		return (1);
	}
	while (match && (*arr || *match))
	{
		if (!*arr)
			printf("%s: mismatch at idx %zu, "
				"found null pointer, expected \"%s\"\n", fn, idx, *match);
		else if (!*match)
			printf("%s: mismatch at idx %zu, "
				"found \"%s\", expected null pointer\n", fn, idx, *arr);
		else if (strcmp(*arr, *match))
			printf("%s: mismatch at idx %zu, "
				"found \"%s\", expected \"%s\"\n", fn, idx, *arr, *match);
		else
		{
			arr++;
			match++;
			idx++;
			continue ;
		}
		return (1);
	}
	return (0);
}

#define CHECK_STRARR(s, c, match) \
do { \
	char **arr = ft_split(s, c); \
	fail = check_strarr("ft_split(\"" s "\", " #c ")", arr, match) || fail; \
	char **iter = arr; \
	while (*iter) \
		free(*iter++); \
	free (arr); \
} while (0)

TEST(ft_split)
{
	int	fail;

	fail = 0;
	/* These tests expect empty strings between multiple separatos */
	/*
	CHECK_STRARR("", '|', ((char *[]){ "", 0 }));
	CHECK_STRARR("abc", '|', ((char *[]){ "abc", 0 }));
	CHECK_STRARR("a|b|c", '|', ((char *[]){ "a", "b", "c", 0 }));
	CHECK_STRARR("a||b", '|', ((char *[]){ "a", "", "b", 0 }));
	CHECK_STRARR("|a|||b|", '|', ((char *[]){ "", "a", "", "", "b", "", 0 }));
	*/
	/* These tests expect empty strings to not be included in the output */
	CHECK_STRARR("", '|', ((char *[]){ 0 }));
	CHECK_STRARR("abc", '|', ((char *[]){ "abc", 0 }));
	CHECK_STRARR("a|b|c", '|', ((char *[]){ "a", "b", "c", 0 }));
	CHECK_STRARR("a||b", '|', ((char *[]){ "a", "b", 0 }));
	CHECK_STRARR("|a|||b|", '|', ((char *[]){ "a", "b", 0 }));
	return (fail);
}
