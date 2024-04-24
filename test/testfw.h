/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testfw.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:19:21 by amakinen          #+#    #+#             */
/*   Updated: 2024/04/24 15:48:07 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTFW_H
# define TESTFW_H
# include <stddef.h>

struct s_test_list_node
{
	void					(*test_func)(void);
	const char				*test_name;
	struct s_test_list_node	*next;
};

extern struct s_test_list_node	**g_test_list_tail_next;

# define TEST(n) \
	static void _test_func_##n(void); \
	static struct s_test_list_node _test_entry_##n = { _test_func_##n, #n, 0 }; \
	__attribute__((constructor)) \
	static void _test_reg_##n(void) { \
		*g_test_list_tail_next = &_test_entry_##n; \
		g_test_list_tail_next = &(_test_entry_##n.next); \
	} \
	static void _test_func_##n(void)

void	testfw_fail(void);

// Set the fail flag for current test, and print message to stderr (accepts printf arguments)
# define TEST_FAIL(...) do { testfw_fail(); fprintf(stderr, __VA_ARGS__); } while (0)

void	mock_write(int fildes);
size_t	unmock_write(int fildes, void **buf);
void	check_unmock_write(char *fn, int fildes, const void *exp_data, size_t exp_len);

#endif
