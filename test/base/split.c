/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 17:00:36 by amakinen          #+#    #+#             */
/*   Updated: 2024/04/25 17:39:52 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "testfw.h"
#include "libft.h"
#include <stdlib.h>
#include <string.h>

static void	check_strarr(const char *fn, char **arr, char **match)
{
	size_t	idx;

	idx = 0;
	while (match && (*arr || *match))
	{
		if (!*arr)
			TEST_FAIL("%s: mismatch at idx %zu, "
				"found null pointer, expected \"%s\"\n", fn, idx, *match);
		else if (!*match)
			TEST_FAIL("%s: mismatch at idx %zu, "
				"found \"%s\", expected null pointer\n", fn, idx, *arr);
		else if (strcmp(*arr, *match))
			TEST_FAIL("%s: mismatch at idx %zu, "
				"found \"%s\", expected \"%s\"\n", fn, idx, *arr, *match);
		else
		{
			arr++;
			match++;
			idx++;
			continue ;
		}
		return ;
	}
}

static void	check_split(const char *s, char c, char *match[])
{
	char	**arr;
	char	**iter;
	char	*fn;

	fn = malloc(10 + strlen(s) + 6);
	sprintf(fn, "ft_split(\"%s\", %c)", s, c);
	arr = ft_split(s, c);
	if (arr)
		check_strarr(fn, arr, match);
	else
		TEST_FAIL("%s returned null pointer", fn);
	iter = arr;
	while (iter && *iter)
		free(*iter++);
	free (arr);
}

REGISTER_TEST(ft_split);

/* These tests expect empty strings between multiple separatos */
/*
static void	test_ft_split(void)
{
	check_split("", '|', ((char *[]){"", 0}));
	check_split("abc", '|', ((char *[]){"abc", 0}));
	check_split("a|b|c", '|', ((char *[]){"a", "b", "c", 0}));
	check_split("a||b", '|', ((char *[]){"a", "", "b", 0}));
	check_split("|a|||b|", '|', ((char *[]){"", "a", "", "", "b", "", 0}));
}
*/

/* These tests expect empty strings to not be included in the output */
static void	test_ft_split(void)
{
	check_split("", '|', ((char *[]){0}));
	check_split("abc", '|', ((char *[]){"abc", 0}));
	check_split("a|b|c", '|', ((char *[]){"a", "b", "c", 0}));
	check_split("a||b", '|', ((char *[]){"a", "b", 0}));
	check_split("|a|||b|", '|', ((char *[]){"a", "b", 0}));
}
