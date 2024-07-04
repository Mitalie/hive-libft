/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mock_write.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 14:13:19 by amakinen          #+#    #+#             */
/*   Updated: 2024/06/17 14:19:44 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <assert.h>
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static ssize_t				(*g_real_write)(int fildes,
		const void *buf, size_t nbyte) = 0;

static struct s_mock_data	*g_mocks = 0;
static int					g_max_mock_fd = -1;

ssize_t	write(int fildes, const void *buf, size_t nbyte)
{
	struct s_mock_data	*mock;

	if (!g_real_write)
		g_real_write = dlsym(RTLD_NEXT, "write");
	if (fildes >= 0 && fildes <= g_max_mock_fd && g_mocks[fildes].buf)
	{
		mock = &g_mocks[fildes];
		mock->buf = realloc(mock->buf, mock->buf_len + nbyte);
		assert(mock->buf);
		memcpy(mock->buf + mock->buf_len, buf, nbyte);
		mock->buf_len += nbyte;
		return (nbyte);
	}
	return (g_real_write(fildes, buf, nbyte));
}

void	mock_write(int fildes)
{
	if (fildes > g_max_mock_fd)
	{
		g_mocks = realloc(g_mocks, sizeof (*g_mocks) * (fildes + 1));
		assert(g_mocks);
		while (g_max_mock_fd < fildes)
			g_mocks[++g_max_mock_fd].buf = 0;
	}
	assert(g_mocks[fildes].buf == 0);
	g_mocks[fildes].buf = malloc(0);
	g_mocks[fildes].buf_len = 0;
}

size_t	unmock_write(int fildes, void **buf)
{
	assert(fildes <= g_max_mock_fd && g_mocks[fildes].buf);
	*buf = g_mocks[fildes].buf;
	g_mocks[fildes].buf = 0;
	return (g_mocks[fildes].buf_len);
}

__attribute__((destructor))
static void	free_mocks_array(void)
{
	free(g_mocks);
}
