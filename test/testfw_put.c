/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testfw_put.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 12:45:48 by amakinen          #+#    #+#             */
/*   Updated: 2024/04/24 15:50:22 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "testfw.h"
#include "libft.h"

#define CHECK_MOCKED_WRITE(expr, fd, expdata, explen) \
do { \
	mock_write(fd); \
	expr \
	check_unmock_write(#expr, fd, expdata, explen); \
} while (0)

#define CHECK_PUTCHAR(fd, c) CHECK_MOCKED_WRITE(ft_putchar_fd(c[0], fd);, fd, c, 1)

TEST(ft_putchar_fd)
{
	CHECK_PUTCHAR(1, "a");
	CHECK_PUTCHAR(9, "b");
	CHECK_PUTCHAR(5, "\0");
}

#define CHECK_PUTSTR(fd, s, l) CHECK_MOCKED_WRITE(ft_putstr_fd(s, fd);, fd, s, l)

TEST(ft_putstr_fd)
{
	CHECK_PUTSTR(2, "abc", 3);
	CHECK_PUTSTR(3, "def\n\tghi.", 9);
	CHECK_PUTSTR(4, "abc\0def", 3);
}

#define CHECK_PUTENDL(fd, s, e) CHECK_MOCKED_WRITE(ft_putendl_fd(s, fd);, fd, e, sizeof(e) - 1)

TEST(ft_putendl_fd)
{
	CHECK_PUTENDL(2, "abc", "abc\n");
	CHECK_PUTENDL(3, "def\n\tghi.", "def\n\tghi.\n");
	CHECK_PUTENDL(4, "abc\0def", "abc\n");
}

#define CHECK_PUTNBR(fd, n) CHECK_MOCKED_WRITE(ft_putnbr_fd(n, fd);, fd, #n, sizeof(#n) - 1)

TEST(ft_putnbr_fd)
{
	CHECK_PUTNBR(2, 2147483647);
	CHECK_PUTNBR(3, 2147483646);
	CHECK_PUTNBR(0, 999);
	CHECK_PUTNBR(0, 1);
	CHECK_PUTNBR(0, 0);
	CHECK_PUTNBR(0, -1);
	CHECK_PUTNBR(0, -999);
	CHECK_PUTNBR(1, -2147483647);
	CHECK_PUTNBR(1, -2147483648);
}
