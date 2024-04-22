/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testfw_cmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 15:09:47 by amakinen          #+#    #+#             */
/*   Updated: 2024/04/22 16:42:20 by amakinen         ###   ########.fr       */
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
		printf("ft_" #fn "(\"%s\", \"%s\", %d) failed: " \
			"ft_ returned %d, std returned %d\n", \
			s1, s2, n, ft_r, std_r); \
		fail = 1; \
	}

#define TESTCMP(n) \
TEST(ft_##n)\
{\
	int	fail;\
	int ft_r;\
	int std_r;\
\
	fail = 0;\
	MATCHCMP(n, "abc", "abc", 4)\
	MATCHCMP(n, "abc", "abd", 4)\
	MATCHCMP(n, "abc", "abd", 2)\
	MATCHCMP(n, "\0abc", "\0abd", 3)\
	MATCHCMP(n, "\0abc", "\0abd", 4)\
	MATCHCMP(n, "a\0bc", "a\0bd", 4)\
	MATCHCMP(n, "a\0bc", "b\0bc", 4)\
	return (fail);\
}

TESTCMP(memcmp)
TESTCMP(strncmp)
