/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testfw_cmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 15:09:47 by amakinen          #+#    #+#             */
/*   Updated: 2024/04/24 16:59:09 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "testfw.h"
#include "libft.h"
#include <string.h>
#include <stdio.h>

#define MATCHCMP(fn, s1, s2, n) \
	ft_r = ft_##fn(s1, s2, n); \
	std_r = fn(s1, s2, n); \
	if (ft_r != std_r) \
	{ \
		TEST_FAIL("ft_" #fn "(\"%s\", \"%s\", %d) failed: " \
			"ft_ returned %d, std returned %d\n", \
			s1, s2, n, ft_r, std_r); \
	}

#define TESTCMP(n) \
REGISTER_TEST(ft_##n);\
\
static void	test_ft_##n(void)\
{\
	int ft_r;\
	int std_r;\
\
	MATCHCMP(n, "abc", "abc", 4)\
	MATCHCMP(n, "abc", "abd", 4)\
	MATCHCMP(n, "abc", "abd", 2)\
	MATCHCMP(n, "\0abc", "\0abd", 3)\
	MATCHCMP(n, "\0abc", "\0abd", 4)\
	MATCHCMP(n, "a\0bc", "a\0bd", 4)\
	MATCHCMP(n, "a\0bc", "b\0bc", 4)\
}

TESTCMP(memcmp);
TESTCMP(strncmp);
