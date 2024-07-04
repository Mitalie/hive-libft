/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strnstr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 15:03:35 by amakinen          #+#    #+#             */
/*   Updated: 2024/04/25 15:14:20 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "testfw.h"
#include "libft.h"
#include <string.h>

static void	match_strnstr(const char *haystack, const char *needle, size_t len)
{
	char	*ft_r;
	char	*std_r;

	std_r = strnstr(haystack, needle, len);
	ft_r = ft_strnstr(haystack, needle, len);
	if (ft_r != std_r)
		TEST_FAIL("ft_strnstr(\"%s\", \"%s\", %zu) failed: "
			"ft_ returned \"%s\" (%p), std returned \"%s\" (%p)\n",
			haystack, needle, len, ft_r, ft_r, std_r, std_r);
}

REGISTER_TEST(ft_strnstr);

static void	test_ft_strnstr(void)
{
	match_strnstr("abcd", "abcd", 4);
	match_strnstr("abcd", "abcd", 3);
	match_strnstr("abcd", "bc", 4);
	match_strnstr("abcd", "bc", 3);
	match_strnstr("abcd", "bc", 2);
	match_strnstr("abcd", "cd", 4);
	match_strnstr("abcd", "cd", 3);
	match_strnstr("abcd", "a", 5);
	match_strnstr("abcd", "a", 1);
	match_strnstr("abcd", "a", 0);
	match_strnstr("\0abcd", "a", 5);
	match_strnstr("abcd", "", 5);
	match_strnstr("abcd", "", 1);
	match_strnstr("abcd", "", 0);
	match_strnstr("abcd", "\0a", 4);
	match_strnstr("abcd", "\0a", 1);
	match_strnstr("abcd", "\0a", 0);
	match_strnstr("abcd", "abcde", 5);
	match_strnstr("abcd", "abcde", 4);
	match_strnstr("abcd", "abce", 4);
	match_strnstr("abcd", "abce", 3);
	match_strnstr("abcd", "cb", 4);
	match_strnstr(0, "", 1);
	match_strnstr(0, "", 0);
}
