/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testfw_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:39:43 by amakinen          #+#    #+#             */
/*   Updated: 2024/04/24 15:56:14 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "testfw.h"
#include <stdio.h>
#include <stdbool.h>

static struct s_test_list_node	*g_test_list_head = 0;
struct s_test_list_node			**g_test_list_tail_next = &g_test_list_head;
static bool						g_current_failed;

static void	print_result(bool failed, const char *name)
{
	if (failed)
		fprintf(stderr, "%s \e[0;31mfailed\e[0m\n", name);
	else
		fprintf(stderr, "%s \e[0;32mpassed\e[0m\n", name);
}

void	testfw_fail(void)
{
	g_current_failed = true;
}

int	main(void)
{
	int						count;
	int						count_success;
	struct s_test_list_node	*test;

	fprintf(stderr, "\e[0;33mRunning tests...\e[0m\n\n");
	count = 0;
	count_success = 0;
	test = g_test_list_head;
	while (test)
	{
		g_current_failed = false;
		test->test_func();
		print_result(g_current_failed, test->test_name);
		count++;
		if (!g_current_failed)
			count_success++;
		test = test->next;
	}
	if (count_success != count)
	{
		fprintf(stderr, "\n\e[0;33m%d/%d tests passed\e[0m\n", count_success, count);
		return (1);
	}
	fprintf(stderr, "\n\e[0;32m%d/%d tests passed\e[0m\n", count_success, count);
	return (0);
}
