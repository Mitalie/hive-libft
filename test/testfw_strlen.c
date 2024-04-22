/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testfw_strlen.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 17:22:59 by amakinen          #+#    #+#             */
/*   Updated: 2024/04/22 17:26:36 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "testfw.h"
#include "libft.h"
#include <string.h>
#include <stdio.h>

#define MATCHSTRLEN(s) \
	ft_r = ft_strlen(s); \
	std_r = strlen(s); \
	if (ft_r != std_r) \
	{ \
		printf("ft_strlen(\"%s\") failed: " \
			"ft_ returned %zu, std returned %zu\n", \
			s, ft_r, std_r); \
		fail = 1; \
	}

TEST(ft_strlen)
{
	int		fail;
	size_t	ft_r;
	size_t	std_r;

	fail = 0;
	MATCHSTRLEN("abc")
	MATCHSTRLEN("abcd")
	MATCHSTRLEN("")
	MATCHSTRLEN("\0")
	MATCHSTRLEN("ab\0c")
	return (fail);
}
