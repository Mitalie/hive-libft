/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testfw_mock_write.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 11:56:33 by amakinen          #+#    #+#             */
/*   Updated: 2024/06/24 19:27:31 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "testfw.h"
#include "testfw_internal.h"
#include <assert.h>
#include <dlfcn.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static ssize_t				(*g_real_write)(int fildes,
		const void *buf, size_t nbyte) = 0;

static struct s_mock_data	*g_mocks = 0;
static int					g_max_mock_fd = -1;

// Stored buffer in mocks is appended with a null byte to make it usable with
// printf %s in testfw_unmock_write_check

ssize_t	write(int fildes, const void *buf, size_t nbyte)
{
	struct s_mock_data	*mock;

	if (!g_real_write)
		g_real_write = dlsym(RTLD_NEXT, "write");
	if (fildes >= 0 && fildes <= g_max_mock_fd && g_mocks[fildes].buf)
	{
		assert(nbyte);
		mock = &g_mocks[fildes];
		mock->buf = realloc(mock->buf, mock->buf_len + nbyte + 1);
		assert(mock->buf);
		memcpy(mock->buf + mock->buf_len, buf, nbyte);
		mock->buf_len += nbyte;
		((char *)mock->buf)[mock->buf_len] = 0;
		return (nbyte);
	}
	return (g_real_write(fildes, buf, nbyte));
}

void	testfw_mock_write(int fildes)
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

size_t	testfw_unmock_write(int fildes, void **buf)
{
	assert(fildes <= g_max_mock_fd && g_mocks[fildes].buf);
	*buf = g_mocks[fildes].buf;
	g_mocks[fildes].buf = 0;
	return (g_mocks[fildes].buf_len);
}

void	testfw_unmock_write_check(int fildes, char *fn,
	const void *exp_data, size_t exp_len)
{
	void	*buf;
	size_t	len;

	len = testfw_unmock_write(fildes, &buf);
	if (len != exp_len)
		TEST_FAIL("%s: captured write length %zu doesn't match expected %zu\n",
			fn, len, exp_len);
	else if (memcmp(buf, exp_data, exp_len))
		TEST_FAIL("%s: captured data \"%s\" doesn't match expected \"%s\"\n",
			fn, (char *)buf, (char *)exp_data);
	free(buf);
}

__attribute__((destructor))
static void	free_mocks_array(void)
{
	free(g_mocks);
}
