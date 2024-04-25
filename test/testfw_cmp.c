/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testfw_cmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 15:09:47 by amakinen          #+#    #+#             */
/*   Updated: 2024/04/25 16:18:00 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "testfw.h"
#include "libft.h"
#include <string.h>

static void	match_memcmp(char *s1, char *s2, size_t n)
{
	int	ft_r;
	int	std_r;

	ft_r = ft_memcmp(s1, s2, n);
	std_r = memcmp(s1, s2, n);
	if ((ft_r < 0 && !(std_r < 0)) || (ft_r > 0 && !(std_r > 0)))
	{
		TEST_FAIL("ft_memcmp(\"%s\", \"%s\", %zu) failed: "
			"ft_ returned %d, std returned %d\n",
			s1, s2, n, ft_r, std_r);
	}
}

REGISTER_TEST(ft_memcmp);

static void	test_ft_memcmp(void)
{
	match_memcmp("abc", "abc", 4);
	match_memcmp("abc", "abd", 4);
	match_memcmp("abc", "abd", 2);
	match_memcmp("\0abc", "\0abd", 3);
	match_memcmp("\0abc", "\0abd", 4);
	match_memcmp("a\0bc", "a\0bd", 4);
	match_memcmp("a\0bc", "b\0bc", 4);
}

static void	match_strncmp(char *s1, char *s2, size_t n)
{
	int	ft_r;
	int	std_r;

	ft_r = ft_strncmp(s1, s2, n);
	std_r = strncmp(s1, s2, n);
	if ((ft_r < 0 && !(std_r < 0)) || (ft_r > 0 && !(std_r > 0)))
	{
		TEST_FAIL("ft_strncmp(\"%s\", \"%s\", %zu) failed: "
			"ft_ returned %d, std returned %d\n",
			s1, s2, n, ft_r, std_r);
	}
}

REGISTER_TEST(ft_strncmp);

static void	test_ft_strncmp(void)
{
	match_strncmp("abc", "abc", 4);
	match_strncmp("abc", "abd", 4);
	match_strncmp("abc", "abd", 2);
	match_strncmp("abcd", "abc", 4);
	match_strncmp("abc", "abcd", 4);
	match_strncmp("abc", "abcd", 3);
	match_strncmp("a\0bc", "a\0bd", 4);
	match_strncmp("a\0bc", "b\0bc", 4);
}
