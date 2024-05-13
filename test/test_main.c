/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 18:17:27 by amakinen          #+#    #+#             */
/*   Updated: 2024/05/13 13:12:10 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "utils.h"
#include <limits.h>
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
		printf("\e[32m ✓ printf(%s)\n\e[0m", #__VA_ARGS__);                               \
	else                                                                                  \
		printf("\e[31m ✗ printf(%s)\n\e[0m", #__VA_ARGS__);                               \
	if (ft_ret != std_ret)                                                                \
		printf("  \e[91mft returned %d, std returned %d\n\e[0m", ft_ret, std_ret);        \
	if (ft_len != std_len || memcmp(ft_out, std_out, ft_len))                             \
	{                                                                                     \
		printf("  \e[91mft wrote %zu bytes:\n\e[95m", ft_len);                            \
		fflush(stdout);                                                                   \
		dump_buffer(ft_out, ft_len, 4);                                                   \
		printf("  \e[91mstd wrote %zu bytes:\n\e[94m", std_len);                          \
		fflush(stdout);                                                                   \
		dump_buffer(std_out, std_len, 4);                                                 \
		printf("\e[0m");                                                                  \
	}                                                                                     \
	free(ft_out);                                                                         \
	free(std_out);                                                                        \
	fflush(stdout);                                                                       \
} while (0)

int	main(void)
{
	printf("\e[93mBasic requirements\e[0m\n");
	test("%c %c %c %c %c", 0, 'a', "ä"[0], "ä"[1], '\n');
	test("%s %s %s", "Hello\nworld!", "åäö", "42");
	test("%p %p %p", (void *)0, main, ft_printf);
	test("%d %d %d %d %d %d %d", INT_MIN, -100, -99, 0, 99, 100, INT_MAX);
	test("%i %i %i %i %i %i %i", INT_MIN, -100, -99, 0, 99, 100, INT_MAX);
	test("%u %u %u %u %u", 0, 15, 165, 65536, UINT_MAX);
	test("%x %x %x %x %x", 0, 15, 165, 65536, UINT_MAX);
	test("%X %X %X %X %X", 0, 15, 165, 65536, UINT_MAX);
	test("%c %% %c %% %c", 'a', 'b', 'c');
	printf("\e[93mWidth\e[0m\n");
	test("%3c %1c %4c %2c %40c", 0, 'a', "ä"[0], "ä"[1], '\n');
	test("%5s %11s %20s", "Hello\nworld!", "åäö", "42");
	test("%65p %1p %8p", (void *)0, main, ft_printf);
	test("%1d %6d %d %12d %3d %1d %15d", INT_MIN, -100, -99, 0, 99, 100, INT_MAX);
	test("%1i %6i %i %12i %3i %1i %15i", INT_MIN, -100, -99, 0, 99, 100, INT_MAX);
	test("%2u %1u %6u %11u %3u", 0, 15, 165, 65536, UINT_MAX);
	test("%2x %1x %6x %11x %3x", 0, 15, 165, 65536, UINT_MAX);
	test("%2X %1X %6X %11X %3X", 0, 15, 165, 65536, UINT_MAX);
	printf("\e[93mWidth, left-justfied\e[0m\n");
	test("%-3c %-1c %-4c %-2c %-40c", 0, 'a', "ä"[0], "ä"[1], '\n');
	test("%-5s %-s %-20s", "Hello\nworld!", "åäö", "42");
	test("%-65p %-2p %-p", (void *)0, main, ft_printf);
	test("%-1d %-6d %-d %-12d %-3d %-1d %-15d", INT_MIN, -100, -99, 0, 99, 100, INT_MAX);
	test("%-1i %-6i %-i %-12i %-3i %-1i %-15i", INT_MIN, -100, -99, 0, 99, 100, INT_MAX);
	test("%-2u %-1u %-u %-11u %-3u", 0, 15, 165, 65536, UINT_MAX);
	test("%-2x %-1x %-x %-11x %-3x", 0, 15, 165, 65536, UINT_MAX);
	test("%-2X %-1X %-X %-11X %-3X", 0, 15, 165, 65536, UINT_MAX);
	printf("\e[93mWidth, zero-padded\e[0m\n");
	test("%01d %06d %0d %012d %03d %01d %015d", INT_MIN, -100, -99, 0, 99, 100, INT_MAX);
	test("%01i %06i %0i %012i %03i %01i %015i", INT_MIN, -100, -99, 0, 99, 100, INT_MAX);
	test("%02u %01u %0u %011u %03u", 0, 15, 165, 65536, UINT_MAX);
	test("%02x %01x %0x %011x %03x", 0, 15, 165, 65536, UINT_MAX);
	test("%02X %01X %0X %011X %03X", 0, 15, 165, 65536, UINT_MAX);
	printf("\e[93mPrecision\e[0m\n");
	test("%.0s %.6s %.11s %.0s", "abc", "Hello\nworld!", "åäö", "42");
	test("%.0d %.0d %.1d %.6d %.d %.12d %.3d %.1d %.15d", 0, 1, INT_MIN, -100, -99, 0, 99, 100, INT_MAX);
	test("%.0i %.0i %.1i %.6i %.i %.12i %.3i %.1i %.15i", 0, 1, INT_MIN, -100, -99, 0, 99, 100, INT_MAX);
	test("%.0u %.0u %.2u %.1u %.6u %.11u %.3u", 0, 1, 0, 15, 165, 65536, UINT_MAX);
	test("%.0x %.0x %.2x %.1x %.6x %.11x %.3x", 0, 1, 0, 15, 165, 65536, UINT_MAX);
	test("%.0X %.0X %.2X %.1X %.6X %.11X %.3X", 0, 1, 0, 15, 165, 65536, UINT_MAX);
	printf("\e[93mAlternate form\e[0m\n");
	test("%#2x %#1x %#x %#11x %#3x", 0, 15, 165, 65536, UINT_MAX);
	test("%#2X %#1X %#X %#11X %#3X", 0, 15, 165, 65536, UINT_MAX);
	test("%#02x %#01x %#0x %#011x %#03x", 0, 15, 165, 65536, UINT_MAX);
	test("%#02X %#01X %#0X %#011X %#03X", 0, 15, 165, 65536, UINT_MAX);
	test("%#-2x %#-1x %#-x %#-11x %#-3x", 0, 15, 165, 65536, UINT_MAX);
	test("%#-2X %#-1X %#-X %#-11X %#-3X", 0, 15, 165, 65536, UINT_MAX);
	test("%#-2.1x %#-1x %#-x %#-11x %#-3x", 0, 15, 165, 65536, UINT_MAX);
	test("%#-2.1X %#-1X %#-X %#-11X %#-3X", 0, 15, 165, 65536, UINT_MAX);

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wformat"
	printf("\e[93m(UB, -Wformat) Zero-padded with non-numeric\e[0m\n");
	test("%03c %01c %04c %02c %040c", 0, 'a', "ä"[0], "ä"[1], '\n');
	test("%05s %011s %020s", "Hello\nworld!", "åäö", "42");
	test("%065p %01p %08p", (void *)0, main, ft_printf);
	printf("\e[93m(-Wformat) Left-justified and zero-padded together\e[0m\n");
	test("%-02d %-06d %-0d %-012d %-03d", 1, -1, 12, INT_MAX, INT_MIN);
	printf("\e[93m(UB, -Wformat) Precision with %%c, %%p\e[0m\n");
	test("%.0c %.3c %.1c %.4c %.2c %.40c", 'x', 0, 'a', "ä"[0], "ä"[1], '\n');
	test("%.0p %.65p %.1p %.8p", (void *)0, (void *)0, main, ft_printf);
#pragma GCC diagnostic pop
	printf("\e[93m(UB, ASan warning) Format options with %%\e[0m\n");
	test("%1c %1% %3c %22% %13c", 'a', 'b', 'c');
	test("%1c %01% %3c %022% %13c", 'a', 'b', 'c');
	test("%1c %-1% %3c %-22% %13c", 'a', 'b', 'c');
}
