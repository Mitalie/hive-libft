/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testfw_atoi.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 17:39:33 by amakinen          #+#    #+#             */
/*   Updated: 2024/04/24 16:59:02 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "testfw.h"
#include "libft.h"
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>

#define MATCHATOI(s) \
	ft_r = ft_atoi(s); \
	std_r = atoi(s); \
	if (ft_r != std_r) \
	{ \
		TEST_FAIL("ft_atoi(\"%s\") failed: " \
			"ft_ returned %d, std returned %d\n", \
			s, ft_r, std_r); \
	}

REGISTER_TEST(ft_atoi);

static void	test_ft_atoi(void)
{
	int	ft_r;
	int	std_r;

	MATCHATOI("abc");
	MATCHATOI("abc99");
	MATCHATOI("99abc");
	MATCHATOI("9abc9");
	MATCHATOI("a99bc");
	MATCHATOI("0");
	MATCHATOI("1");
	MATCHATOI("-1");
	MATCHATOI("+1");
	MATCHATOI("--1");
	MATCHATOI("-+1");
	MATCHATOI("+-1");
	MATCHATOI("++1");
	MATCHATOI("999");
	MATCHATOI("-999");
	MATCHATOI("2147483647");
	MATCHATOI("2147483646");
	MATCHATOI("-2147483647");
	MATCHATOI("-2147483648");
}
