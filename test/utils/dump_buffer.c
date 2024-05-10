/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dump_buffer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 13:15:17 by amakinen          #+#    #+#             */
/*   Updated: 2024/05/10 11:21:41 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "util.h"
#include <stdio.h>
#include <string.h>

static char	to_printable(char c)
{
	if (c >= 32 && c <= 126)
		return (c);
	return ('.');
}

static void	hexbyte(char *dst, unsigned char b)
{
	dst[0] = "0123456789abcdef"[b / 16];
	dst[1] = "0123456789abcdef"[b % 16];
}

void	dump_buffer(void *buf, size_t len, int indent)
{
	size_t	pos;
	char	hex[40];
	char	ascii[16];

	pos = 0;
	indent += 8;
	memset(hex, ' ', sizeof hex);
	memset(ascii, ' ', sizeof ascii);
	while (pos < len)
	{
		hexbyte(hex + pos % 16 * 5 / 2, ((char *)buf)[pos]);
		ascii[pos % 16] = to_printable(((char *)buf)[pos]);
		if (++pos == len)
		{
			while (pos % 16)
			{
				hex[pos % 16 * 5 / 2] = ' ';
				hex[pos % 16 * 5 / 2 + 1] = ' ';
				ascii[pos % 16] = ' ';
				pos++;
			}
		}
		if (pos % 16 == 0)
			printf("%*.8zx: %40.40s %16.16s\n", indent, pos - 16, hex, ascii);
	}
}
