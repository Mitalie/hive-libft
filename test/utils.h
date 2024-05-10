/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 13:16:17 by amakinen          #+#    #+#             */
/*   Updated: 2024/05/10 11:20:02 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stddef.h>

struct s_mock_data
{
	void	*buf;
	size_t	buf_len;
};

void	dump_buffer(void *buf, size_t len, int indent);
void	mock_write(int fildes);
size_t	unmock_write(int fildes, void **buf);

#endif
