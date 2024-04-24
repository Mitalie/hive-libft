/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testfw_strl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 17:22:59 by amakinen          #+#    #+#             */
/*   Updated: 2024/04/24 15:51:24 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "testfw.h"
#include "libft.h"
#include <string.h>
#include <stdio.h>

#define MATCHSTRLEN(s) \
	ft_r = ft_strlen(s); \
	std_r = strlen(s); \
	if (ft_r != std_r) \
	{ \
		TEST_FAIL("ft_strlen(\"%s\") failed: " \
			"ft_ returned %zu, std returned %zu\n", \
			s, ft_r, std_r); \
	}

TEST(ft_strlen)
{
	size_t	ft_r;
	size_t	std_r;

	MATCHSTRLEN("abc")
	MATCHSTRLEN("abcd")
	MATCHSTRLEN("")
	MATCHSTRLEN("\0")
	MATCHSTRLEN("ab\0c")
}

#define MATCHSTRLC(f, d, s, l) \
	strcpy(ft_d, d); \
	strcpy(std_d, d); \
	ft_r = ft_##f(ft_d, s, l); \
	std_r = f(std_d, s, l); \
	if (ft_r != std_r || memcmp(ft_d, std_d, 21)) \
	{ \
		TEST_FAIL("ft_" #f "(\"%s\", \"%s\", %d) failed:\n" \
			"\tft_ returned %zu and set dst %s\n" \
			"\tstd returned %zu and set dst %s\n", \
			d, s, l, ft_r, ft_d, std_r, std_d); \
	}

#define MATCHSTRLCPY(s, l) \
	MATCHSTRLC(strlcpy, "12345678901234567890", s, l)

TEST(ft_strlcpy)
{
	char	ft_d[21];
	size_t	ft_r;
	char	std_d[21];
	size_t	std_r;

	MATCHSTRLCPY("abcde", 0)
	MATCHSTRLCPY("abcde", 4)
	MATCHSTRLCPY("abcde", 5)
	MATCHSTRLCPY("abcde", 6)
	MATCHSTRLCPY("abcde", 7)
	MATCHSTRLCPY("", 0)
	MATCHSTRLCPY("", 1)
	MATCHSTRLCPY("", 2)
}

#define MATCHSTRLCAT(d, s, l) \
	strcpy(ft_d, "12345678901234567890"); \
	strcpy(std_d, "12345678901234567890"); \
	MATCHSTRLC(strlcat, d, s, l)

TEST(ft_strlcat)
{
	char	ft_d[21];
	size_t	ft_r;
	char	std_d[21];
	size_t	std_r;

	MATCHSTRLCAT("abc", "def", 0)
	MATCHSTRLCAT("abc", "def", 3)
	MATCHSTRLCAT("abc", "def", 4)
	MATCHSTRLCAT("abc", "def", 5)
	MATCHSTRLCAT("abc", "def", 6)
	MATCHSTRLCAT("abc", "def", 7)
	MATCHSTRLCAT("abc", "def", 8)
	MATCHSTRLCAT("", "def", 0)
	MATCHSTRLCAT("", "def", 1)
	MATCHSTRLCAT("", "def", 2)
	MATCHSTRLCAT("", "def", 3)
	MATCHSTRLCAT("", "def", 4)
	MATCHSTRLCAT("", "def", 5)
	MATCHSTRLCAT("abc", "", 0)
	MATCHSTRLCAT("abc", "", 1)
	MATCHSTRLCAT("abc", "", 2)
	MATCHSTRLCAT("abc", "", 3)
	MATCHSTRLCAT("abc", "", 4)
	MATCHSTRLCAT("abc", "", 5)
}
