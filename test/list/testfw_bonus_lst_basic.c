/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testfw_bonus_lst_basic.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 15:41:51 by amakinen          #+#    #+#             */
/*   Updated: 2024/04/26 17:07:55 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "testfw.h"
#include "libft.h"
#include <stdlib.h>

REGISTER_TEST(ft_lstnew);

// FIXME: mock malloc instead
static void	test_ft_lstnew(void)
{
	t_list	*lst[2];
	int		content[2];

	lst[0] = ft_lstnew(&content[0]);
	lst[1] = ft_lstnew(&content[1]);
	if (!lst[0] || !lst[1])
	{
		TEST_FAIL("ft_lstnew returned null pointer\n");
		free(lst[0]);
		free(lst[1]);
		return ;
	}
	if (lst[0] == lst[1])
		TEST_FAIL("ft_lstnew returned non-unique pointer\n");
	if (lst[0]->content != &content[0] || lst[1]->content != &content[1])
		TEST_FAIL("ft_lstnew did not assign correct content ptr\n");
	if (lst[0]->next || lst[1]->next)
		TEST_FAIL("ft_lstnew did not initialize next\n");
	lst[0]->content = 0;
	lst[0]->next = 0;
	lst[1]->content = 0;
	lst[1]->next = 0;
	free(lst[0]);
	free(lst[1]);
}

REGISTER_TEST(ft_lstsize);

static void	test_ft_lstsize(void)
{
	t_list	lst[5];
	int		i;

	i = 0;
	while (i < 5)
	{
		lst[i].next = 0;
		if (ft_lstsize(&lst[0]) != i + 1)
			TEST_FAIL("ft_lstsize returned wrong size\n");
		lst[i].next = &lst[i + 1];
		i++;
	}
}

REGISTER_TEST(ft_lstlast);

static void	test_ft_lstlast(void)
{
	t_list	lst[5];
	int		i;

	i = 0;
	while (i < 5)
	{
		lst[i].next = 0;
		if (ft_lstlast(&lst[0]) != &lst[i])
			TEST_FAIL("ft_lstlast returned wrong node ptr\n");
		lst[i].next = &lst[i + 1];
		i++;
	}
}
