/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testfw.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:19:21 by amakinen          #+#    #+#             */
/*   Updated: 2024/06/24 19:27:06 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTFW_H
# define TESTFW_H
# include <stddef.h>
# include <stdio.h>

void	testfw_register(char *name, void (*test_func)(void));

// Register a test function to be run. For registration name `n`, the function must be declared as `static void test_n(void)`.
# define REGISTER_TEST(n) \
	static void test_##n(void); \
	__attribute__((constructor)) \
	static void _test_reg_##n(void) { \
		testfw_register(#n, test_##n); \
	}

void	testfw_fail(void);

// Set the fail flag for current test, and print message to stderr (accepts printf arguments)
# define TEST_FAIL(...) do { testfw_fail(); fprintf(stderr, __VA_ARGS__); } while (0)

void	testfw_mock_write(int fildes);
size_t	testfw_unmock_write(int fildes, void **buf);
void	testfw_unmock_write_check(int fildes, char *fn,
			const void *exp_data, size_t exp_len);

#endif
