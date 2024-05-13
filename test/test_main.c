/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 15:50:41 by amakinen          #+#    #+#             */
/*   Updated: 2024/05/13 15:59:37 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include "get_next_line.h"

int	main(void)
{
	size_t	linenbr;
	char	*line;

	linenbr = 1;
	printf("Reading stdin line-by-line...\n");
	line = get_next_line(STDIN_FILENO);
	while (line)
	{
		printf("%5zu: %s", ++linenbr, line);
	}
	printf("\nGot %zu lines\n", linenbr);
}
