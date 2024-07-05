/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:39:43 by amakinen          #+#    #+#             */
/*   Updated: 2024/06/25 14:24:55 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "testfw.h"
#include "internal.h"
#include <assert.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

static struct s_test_list_node	*g_test_list_head = 0;
static struct s_test_list_node	**g_test_list_tail_next = &g_test_list_head;
static bool						g_current_failed;

void	testfw_register(char *test_name, void (*test_func)(void))
{
	struct s_test_list_node	*node;

	node = malloc(sizeof (*node));
	assert(node);
	node->test_func = test_func;
	node->test_name = test_name;
	node->next = 0;
	*g_test_list_tail_next = node;
	g_test_list_tail_next = &node->next;
}

void	testfw_fail(void)
{
	g_current_failed = true;
}

static bool	run_test(struct s_test_list_node *test)
{
	g_current_failed = false;
	test->test_func();
	if (g_current_failed)
		fprintf(stderr, "%s \e[0;31mfailed\e[0m\n", test->test_name);
	else
		fprintf(stderr, "%s \e[0;32mpassed\e[0m\n", test->test_name);
	return (g_current_failed);
}

static void	free_test_list(void)
{
	struct s_test_list_node	*next;

	while (g_test_list_head)
	{
		next = g_test_list_head->next;
		free(g_test_list_head);
		g_test_list_head = next;
	}
	g_test_list_tail_next = &g_test_list_head;
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
		count++;
		if (!run_test(test))
			count_success++;
		test = test->next;
	}
	if (count_success != count)
	{
		fprintf(stderr, "\n\e[0;33m%d/%d tests passed\e[0m\n",
			count_success, count);
		return (1);
	}
	fprintf(stderr, "\n\e[0;32m%d/%d tests passed\e[0m\n",
		count_success, count);
	free_test_list();
	return (0);
}
