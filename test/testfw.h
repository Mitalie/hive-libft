/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testfw.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:19:21 by amakinen          #+#    #+#             */
/*   Updated: 2024/04/22 14:55:49 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTFW_H
# define TESTFW_H

struct s_test_list_node
{
	int						(*test_func)(void);
	const char				*test_name;
	struct s_test_list_node	*next;
};

extern struct s_test_list_node	**g_test_list_tail_next;

# define TEST(n) \
	static int _test_func_##n(void); \
	static struct s_test_list_node _test_entry_##n = { _test_func_##n, #n, 0 }; \
	__attribute__((constructor)) \
	static void _test_reg_##n(void) { \
		*g_test_list_tail_next = &_test_entry_##n; \
		g_test_list_tail_next = &(_test_entry_##n.next); \
	} \
	static int _test_func_##n(void)

#endif
