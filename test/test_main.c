/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 18:17:27 by amakinen          #+#    #+#             */
/*   Updated: 2024/05/09 10:36:20 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

#define test(...) do { \
	int ft = ft_printf(__VA_ARGS__); \
	printf("\n"); \
	int std = printf(__VA_ARGS__); \
	printf("\nft: %d, std %d\n--------\n", ft, std); \
	fflush(stdout); \
} while (0)

int	main(void)
{
	test("|%20p|", (void *)0);
	test("|%-20p|", "a");
	test("|%%|");
}
