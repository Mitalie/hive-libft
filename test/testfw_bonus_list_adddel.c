/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testfw_bonus_list_adddel.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 15:59:43 by amakinen          #+#    #+#             */
/*   Updated: 2024/04/26 17:32:00 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "testfw.h"
#include "libft.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

REGISTER_TEST(ft_lstadd_front);

static void	test_ft_lstadd_front(void)
{
	t_list	lst[5];
	int		content[5];
	t_list	cpy[5];
	t_list	*lstp[2];
	int		i;

	i = 0;
	lstp[0] = 0;
	while (i < 5)
	{
		lst[i].content = &content[i];
		lst[i].next = lstp[0];
		memcpy(&cpy[i], &lst[i], sizeof (*lst));
		lstp[1] = lstp[0];
		ft_lstadd_front(&lstp[0], &lst[i]);
		if (lstp[0] != &lst[i])
			TEST_FAIL("ft_lstadd_front didn't update head pointer correctly\n");
		if (lst[i].next != lstp[1])
			TEST_FAIL("ft_lstadd_front didn't link new node to list\n");
		if (memcmp(lst, cpy, sizeof (*lst) * (i + 1)))
			TEST_FAIL("ft_lstadd_front modified nodes");
		i++;
	}
}

REGISTER_TEST(ft_lstadd_back);

static void	test_ft_lstadd_back(void)
{
	t_list	lst[5];
	int		content[5];
	t_list	cpy[5];
	t_list	*lstp;
	int		i;

	lstp = 0;
	i = 0;
	while (i < 5)
	{
		lst[i].content = &content[i];
		lst[i].next = 0;
		memcpy(&cpy[i], &lst[i], sizeof (*lst));
		ft_lstadd_back(&lstp, &lst[i]);
		if (i == 0 && lstp != &lst[0])
			TEST_FAIL("ft_lstadd_back didn't update empty head pointer\n");
		if (i > 0 && lstp != &lst[0])
			TEST_FAIL("ft_lstadd_back modified head pointer incorrectly\n");
		if (i > 0 && lst[i - 1].next != &lst[i])
			TEST_FAIL("ft_lstadd_back didn't link the new node to list\n");
		if (i > 0)
			cpy[i - 1].next = lst[i - 1].next;
		if (memcmp(lst, cpy, sizeof (*lst) * (++i)))
			TEST_FAIL("ft_lstadd_back modified nodes\n");
	}
}

static void	*g_deleted[5];
static int	g_ndeleted;

static void	del(void *content)
{
	if (g_ndeleted++ > 5)
		return ;
	g_deleted[g_ndeleted - 1] = content;
}

REGISTER_TEST(ft_lstdelone);

// FIXME: mock free and ensure it's called with the correct node ptr
static void	test_ft_lstdelone(void)
{
	t_list	*lst[2];
	int		content[2];

	lst[0] = malloc(sizeof(*lst[0]));
	lst[1] = malloc(sizeof(*lst[1]));
	assert(lst[0] && lst[1]);
	lst[0]->content = &content[0];
	lst[0]->next = 0;
	lst[1]->content = &content[1];
	lst[1]->next = lst[0];
	g_ndeleted = 0;
	ft_lstdelone(lst[1], del);
	if (g_ndeleted != 1)
		TEST_FAIL("ft_lstdelone didn't call del exactly once\n");
	if (g_deleted[0] != &content[1])
		TEST_FAIL("ft_lstdelone didn't call del with the correct ptr\n");
	if (lst[0]->next != 0 || lst[0]->content != &content[0])
		TEST_FAIL("ft_lstdelone modified next node\n");
	free(lst[0]);
}

REGISTER_TEST(ft_lstclear);

// FIXME: mock free and ensure it's called with the node ptrs as expected
static void	test_ft_lstclear(void)
{
	t_list	*lst[2];
	int		content[2];

	lst[0] = malloc(sizeof(*lst[0]));
	lst[1] = malloc(sizeof(*lst[1]));
	assert(lst[0] && lst[1]);
	lst[0]->content = &content[0];
	lst[0]->next = 0;
	lst[1]->content = &content[1];
	lst[1]->next = lst[0];
	g_ndeleted = 0;
	ft_lstclear(&lst[1], del);
	if (g_ndeleted != 2)
		TEST_FAIL("ft_lstclear didn't call del the correct number of times\n");
	if (g_deleted[0] != &content[1] || g_deleted[1] != &content[0])
		TEST_FAIL("ft_lstclear didn't call del with the correct ptrs\n");
	if (lst[1] != 0)
		TEST_FAIL("ft_lstclear didn't set head ptr to null\n");
}
