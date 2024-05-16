/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 15:50:41 by amakinen          #+#    #+#             */
/*   Updated: 2024/05/16 15:49:37 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include "get_next_line.h"

int	main(void)
{
	size_t	linenbr;
	char	*line;
	int		fd;

	linenbr = 0;
	fd = open("test.txt", O_RDONLY);
	printf("Reading test.txt line-by-line...\n");
	line = get_next_line(fd);
	while (line)
	{
		printf("%5zu: %s", ++linenbr, line);
		line = get_next_line(fd);
	}
	printf("\nGot %zu lines\n", linenbr);
}
