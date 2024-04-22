/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testfw_ctype.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 18:17:46 by amakinen          #+#    #+#             */
/*   Updated: 2024/04/22 14:12:20 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "testfw.h"
#include "libft.h"
#include <ctype.h>
#include <limits.h>
#include <stdio.h>

int	test_ctype(int (*ft_f)(int), int (std_f)(int), char *fn, int is_bool)
{
	int	c;
	int	fail;
	int	ft_r;
	int	std_r;

	c = -1;
	fail = 0;
	while (c <= UCHAR_MAX)
	{
		ft_r = ft_f(c);
		std_r = std_f(c);
		if (is_bool)
		{
			ft_r = !!ft_r;
			std_r = !!std_r;
		}
		if (ft_r != std_r)
		{
			printf("ft_%s failed on %d: "
				"ft_ returned %d, standard returned %d\n",
				fn, c, ft_r, std_r);
			fail = 1;
		}
		c++;
	}
	return (fail);
}

#define TEST_CTYPE(n, b) \
	TEST(ft_##n) \
	{ \
		return test_ctype(ft_##n, n, #n, b); \
	}


TEST_CTYPE(isalpha, 1)
TEST_CTYPE(isdigit, 1)
TEST_CTYPE(isalnum, 1)
TEST_CTYPE(isascii, 1)
TEST_CTYPE(isprint, 1)
TEST_CTYPE(toupper, 0)
TEST_CTYPE(tolower, 0)
