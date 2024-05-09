/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 18:17:27 by amakinen          #+#    #+#             */
/*   Updated: 2024/05/09 14:53:35 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define test(...) \
do {                                                                                      \
	mock_write(STDOUT_FILENO);                                                            \
	int ft_ret = ft_printf(__VA_ARGS__);                                                  \
	void *ft_out;                                                                         \
	size_t ft_len = unmock_write(STDOUT_FILENO, &ft_out);                                 \
	void *std_out;                                                                        \
	int std_ret = asprintf((char **)&std_out, __VA_ARGS__);                               \
	size_t std_len = std_ret;                                                             \
	if (ft_ret == std_ret && ft_len == std_len && !memcmp(ft_out, std_out, ft_len))       \
		break; /* good */                                                                 \
	printf("printf(%s)\n", #__VA_ARGS__);                                                 \
	if (ft_ret != std_ret)                                                                \
		printf("ft returned %d, std returned %d\n", ft_ret, std_ret);                     \
	if (ft_len != std_len || memcmp(ft_out, std_out, ft_len))                             \
	{                                                                                     \
		printf("ft wrote %zu bytes:\n", ft_len);                                          \
		dump_buffer(ft_out, ft_len);                                                      \
		printf("std wrote %zu bytes:\n", std_len);                                        \
		dump_buffer(std_out, std_len);                                                    \
	}                                                                                     \
	free(ft_out);                                                                         \
	free(std_out);                                                                        \
	fflush(stdout);                                                                       \
} while (0)

int	main(void)
{
	test("|%20p|", (void *)0);
	test("|%-20p|", "a");
	test("|%f|", 0.0);
}
