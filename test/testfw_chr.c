/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testfw_chr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 16:05:44 by amakinen          #+#    #+#             */
/*   Updated: 2024/04/25 16:46:08 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "testfw.h"
#include "libft.h"
#include <string.h>

static void	match_strchr(int reverse, const char *s, int c)
{
	char	*ft_r;
	char	*std_r;
	char	*fn;

	if (reverse)
	{
		ft_r = ft_strrchr(s, c);
		std_r = strrchr(s, c);
		fn = "strrchr";
	}
	else
	{
		ft_r = ft_strchr(s, c);
		std_r = strchr(s, c);
		fn = "strchr";
	}
	if (ft_r != std_r)
		TEST_FAIL("ft_%s(\"%s\", '%c'<%d>) failed: "
			"ft_ returned \"%s\" (%p), std returned \"%s\" (%p)\n",
			fn, s, c, c, ft_r, ft_r, std_r, std_r);
}

REGISTER_TEST(strchr);

static void	test_strchr(void)
{
	match_strchr(0, "abc", 'a');
	match_strchr(0, "abc", 'b');
	match_strchr(0, "abc", 'c');
	match_strchr(0, "abc", '\0');
	match_strchr(0, "abc", 'd');
	match_strchr(0, "abc", 'A');
	match_strchr(0, "abc", 'a' + 1024);
	match_strchr(0, "a\300c", 0300 + 1024);
}

REGISTER_TEST(strrchr);

static void	test_strrchr(void)
{
	match_strchr(1, "abc", 'a');
	match_strchr(1, "abc", 'b');
	match_strchr(1, "abc", 'c');
	match_strchr(1, "abc", '\0');
	match_strchr(1, "abc", 'd');
	match_strchr(1, "abc", 'A');
	match_strchr(1, "abc", 'a' + 1024);
	match_strchr(1, "a\300c", 0300 + 1024);
}

static void	match_memchr(const char *s, int c, size_t n)
{
	char	*ft_r;
	char	*std_r;

	ft_r = ft_memchr(s, c, n);
	std_r = memchr(s, c, n);
	if (ft_r != std_r)
		TEST_FAIL("ft_memchr(\"%s\", '%c'<%d>, %zu) failed: "
			"ft_ returned \"%s\" (%p), std returned \"%s\" (%p)\n",
			s, c, c, n, ft_r, ft_r, std_r, std_r);
}

REGISTER_TEST(ft_memchr);

static void	test_ft_memchr(void)
{
	match_memchr("abc", 'a', 4);
	match_memchr("abc", 'b', 4);
	match_memchr("abc", 'c', 4);
	match_memchr("abc", '\0', 4);
	match_memchr("abc", '\0', 3);
	match_memchr("abc", 'd', 4);
	match_memchr("abc", 'A', 4);
	match_memchr("abc", 'a' + 1024, 4);
	match_memchr("abc", 'a' + 1024, 0);
	match_memchr("a\300c", 0300 + 1024, 3);
}
