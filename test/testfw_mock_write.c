/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testfw_mock_write.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 11:56:33 by amakinen          #+#    #+#             */
/*   Updated: 2024/04/24 15:49:51 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "testfw.h"
#include <assert.h>
#include <dlfcn.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static ssize_t (*real_write)(int fildes, const void *buf, size_t nbyte) = 0;

struct mock_data {
	void	*buf;
	size_t	buf_len;
};

static struct mock_data *mocks = 0;
static int				max_mock_fd = -1;

static ssize_t	mocked_write(int fildes, const void *buf, size_t nbyte)
{
	struct mock_data	*mock;

	assert(nbyte);
	mock = &mocks[fildes];
	mock->buf = realloc(mock->buf, mock->buf_len + nbyte + 1);
	assert(mock->buf);
	memcpy(mock->buf + mock->buf_len, buf, nbyte);
	mock->buf_len += nbyte;
	((char *)mock->buf)[mock->buf_len] = 0; // null terminator for printf("%s") in check_unmock_write
	return (nbyte);
}

ssize_t	write(int fildes, const void *buf, size_t nbyte)
{
	if (!real_write)
		real_write = dlsym(RTLD_NEXT, "write");
	if (fildes >= 0 && fildes <= max_mock_fd && mocks[fildes].buf)
		return (mocked_write(fildes, buf, nbyte));
	return (real_write(fildes, buf, nbyte));
}

void	mock_write(int fildes)
{
	if (fildes > max_mock_fd)
	{
		mocks = realloc(mocks, sizeof (*mocks) * (fildes + 1));
		assert(mocks);
		while (max_mock_fd < fildes)
			mocks[++max_mock_fd].buf = 0;
	}
	assert(mocks[fildes].buf == 0);
	mocks[fildes].buf = malloc(0);
	mocks[fildes].buf_len = 0;
}

size_t	unmock_write(int fildes, void **buf)
{
	assert(fildes <= max_mock_fd && mocks[fildes].buf);
	*buf = mocks[fildes].buf;
	mocks[fildes].buf = 0;
	return mocks[fildes].buf_len;
}

void	check_unmock_write(char *fn, int fildes, const void *exp_data, size_t exp_len)
{
	void	*buf;
	size_t	len;

	len = unmock_write(fildes, &buf);
	if (len != exp_len)
		TEST_FAIL("%s: captured write length %zu doesn't match expected %zu\n",
			fn, len, exp_len);
	else if (memcmp(buf, exp_data, exp_len))
		TEST_FAIL("%s: captured data \"%s\" doesn't match expected \"%s\"\n",
			fn, (char *)buf, (char *)exp_data);
	free(buf);
}
