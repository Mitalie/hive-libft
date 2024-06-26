/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_putnbr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 11:40:03 by amakinen          #+#    #+#             */
/*   Updated: 2024/04/18 11:43:13 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <limits.h>

void	test_putnbr(int n)
{
	ft_putnbr_fd(n, 1);
	printf("\n%d\n", n);
}

int	main(void)
{
	test_putnbr(INT_MAX);
	test_putnbr(INT_MAX - 1);
	test_putnbr(1234);
	test_putnbr(99);
	test_putnbr(1);
	test_putnbr(0);
	test_putnbr(-1);
	test_putnbr(-99);
	test_putnbr(-1234);
	test_putnbr(INT_MIN + 1);
	test_putnbr(INT_MIN);
}
