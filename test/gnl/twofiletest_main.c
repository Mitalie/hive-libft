/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   twofiletest_main.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 15:56:22 by amakinen          #+#    #+#             */
/*   Updated: 2024/05/16 16:12:44 by amakinen         ###   ########.fr       */
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
	size_t	linenbr1;
	size_t	linenbr2;
	char	*line1;
	char	*line2;
	int		fd1;
	int		fd2;

	linenbr1 = 0;
	linenbr2 = 0;
	fd1 = open("test.txt", O_RDONLY);
	fd2 = open("test2.txt", O_RDONLY);
	printf("Reading test.txt and test2.txt line-by-line...\n");
	line1 = get_next_line(fd1);
	line2 = get_next_line(fd2);
	while (line1 || line2)
	{
		if (line1)
		{
			printf("%5zu: $", ++linenbr1);
			printstr_escaped(line1);
			printf("$\n");
			line1 = get_next_line(fd1);
		}
		if (line2)
		{
			printf("%5zu: $", ++linenbr2);
			printstr_escaped(line2);
			printf("$\n");
			line2 = get_next_line(fd2);
		}
	}
	printf("Got %zu lines from test.txt\n", linenbr1);
	printf("Got %zu lines from test2.txt\n", linenbr2);
}
