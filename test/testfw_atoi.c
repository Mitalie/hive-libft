/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testfw_atoi.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 17:39:33 by amakinen          #+#    #+#             */
/*   Updated: 2024/04/25 11:34:31 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "testfw.h"
#include "libft.h"
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>

static void	match_atoi(const char *s)
{
	int	ft_r;
	int	std_r;

	ft_r = ft_atoi(s);
	std_r = atoi(s);
	if (ft_r != std_r)
	{
		TEST_FAIL("ft_atoi(\"%s\") failed: "
			"ft_ returned %d, std returned %d\n",
			s, ft_r, std_r);
	}
}

REGISTER_TEST(ft_atoi);

static void	test_ft_atoi(void)
{
	match_atoi("abc");
	match_atoi("abc99");
	match_atoi("99abc");
	match_atoi("9abc9");
	match_atoi("a99bc");
	match_atoi("0");
	match_atoi("1");
	match_atoi("-1");
	match_atoi("+1");
	match_atoi("--1");
	match_atoi("-+1");
	match_atoi("+-1");
	match_atoi("++1");
	match_atoi("999");
	match_atoi("-999");
	match_atoi("2147483647");
	match_atoi("2147483646");
	match_atoi("-2147483647");
	match_atoi("-2147483648");
}
