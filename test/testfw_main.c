/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testfw_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:39:43 by amakinen          #+#    #+#             */
/*   Updated: 2024/04/22 17:38:08 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "testfw.h"
#include <stdio.h>

static struct s_test_list_node	*g_test_list_head = 0;
struct s_test_list_node			**g_test_list_tail_next = &g_test_list_head;

static void	print_result(int status, const char *name)
{
	if (status == 0)
		printf("%s \e[0;32mpassed\e[0m\n", name);
	else
		printf("%s \e[0;31mfailed\e[0m\n", name);
}

int	main(void)
{
	int						status;
	int						count;
	int						count_success;
	struct s_test_list_node	*test;

	printf("\e[0;33mRunning tests...\e[0m\n\n");
	count = 0;
	count_success = 0;
	test = g_test_list_head;
	while (test)
	{
		status = test->test_func();
		print_result(status, test->test_name);
		count++;
		if (status == 0)
			count_success++;
		test = test->next;
	}
	if (count_success != count)
	{
		printf("\n\e[0;33m%d/%d tests passed\e[0m\n", count_success, count);
		return (1);
	}
	printf("\n\e[0;32m%d/%d tests passed\e[0m\n", count_success, count);
	return (0);
}
