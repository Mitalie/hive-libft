/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testfw_bonus_list_iter.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 17:21:37 by amakinen          #+#    #+#             */
/*   Updated: 2024/04/29 11:09:36 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "testfw.h"
#include "libft.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

static void	*g_iterated[5];
static int	g_niterated;

static void	testiter(void *content)
{
	if (g_niterated++ > 5)
		return ;
	g_iterated[g_niterated - 1] = content;
}

REGISTER_TEST(ft_lstiter);

static void	test_ft_lstiter(void)
{
	t_list	lst[5];
	t_list	cpy[5];
	int		content[5];
	int		i;

	lst[0] = (t_list){&content[0], 0};
	i = 1;
	while (i < 5)
	{
		lst[i] = (t_list){&content[i], &lst[i - 1]};
		i++;
	}
	memcpy(cpy, lst, sizeof(lst));
	g_niterated = 0;
	ft_lstiter(&lst[4], testiter);
	if (g_niterated != 5)
		TEST_FAIL("ft_lstiter didn't call iter the correct number of times\n");
	if (g_iterated[0] != &content[4] || g_iterated[1] != &content[3]
		|| g_iterated[2] != &content[2] || g_iterated[3] != &content[1]
		|| g_iterated[4] != &content[0])
		TEST_FAIL("ft_lstiter didn't call iter with correct content ptrs\n");
	if (memcmp(cpy, lst, sizeof(lst)))
		TEST_FAIL("ft_lstiter modified the list\n");
}

static void	*testmap(void *content)
{
	char	*dup;
	int		idx;

	dup = strdup(content);
	idx = 0;
	while (dup[idx])
	{
		dup[idx] = toupper(dup[idx]);
		idx++;
	}
	return (dup);
}

REGISTER_TEST(ft_lstmap);

// FIXME: mock malloc fail, ensure free and del are called properly
static void	test_ft_lstmap(void)
{
	t_list	lst[3];
	t_list	cpy[3];
	t_list	*mapped;
	t_list	*next;

	lst[0] = (t_list){"abc", 0};
	lst[1] = (t_list){"def", &lst[0]};
	lst[2] = (t_list){"ghi", &lst[1]};
	memcpy(cpy, lst, sizeof(lst));
	mapped = ft_lstmap(&lst[2], testmap, free);
	if (memcmp(cpy, lst, sizeof(lst)))
		TEST_FAIL("ft_lstmap modified the list\n");
	if (strcmp(mapped->content, "GHI")
		|| strcmp(mapped->next->content, "DEF")
		|| strcmp(mapped->next->next->content, "ABC"))
		TEST_FAIL("ft_lstmap didn't return correct mapped content\n");
	while (mapped)
	{
		free(mapped->content);
		next = mapped->next;
		free(mapped);
		mapped = next;
	}
}
