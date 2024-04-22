/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ctype.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 18:17:46 by amakinen          #+#    #+#             */
/*   Updated: 2024/04/22 10:50:26 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	if (fail)
		printf("ft_%s \e[0;31mfailed\e[0m\n", fn);
	else
		printf("ft_%s \e[0;32mpassed\e[0m\n", fn);
	return (fail);
}

#define TEST(n, b) test_ctype(ft_ ## n, n, #n, b)

int	main(void)
{
	TEST(isalpha, 1);
	TEST(isdigit, 1);
	TEST(isalnum, 1);
	TEST(isascii, 1);
	TEST(isprint, 1);
	TEST(toupper, 0);
	TEST(tolower, 0);
}
