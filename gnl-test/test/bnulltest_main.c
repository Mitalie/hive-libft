/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bnulltest_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 17:13:28 by amakinen          #+#    #+#             */
/*   Updated: 2024/05/27 17:50:29 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include "get_next_line.h"

void	printstr_escaped(char *str)
{
	while (*str)
	{
		if (*str == '\n')
			printf("\\n");
		else if (*str < 32 || *str > 126)
			printf("\\x%02x", *str);
		else
			printf("%c", *str);
		str++;
	}
}

int	main(void)
{
	size_t	linenbr;
	char	*line;
	int		fd;

	linenbr = 0;
	fd = open("nulltest.txt", O_RDONLY);
	printf("Reading nulltest.txt line-by-line...\n");
	line = get_next_line(fd);
	while (line)
	{
		printf("%5zu: $", ++linenbr);
		printstr_escaped(line);
		printf("$\n");
		line = get_next_line(fd);
	}
	printf("Got %zu lines\n", linenbr);
}
