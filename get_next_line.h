/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 15:45:20 by amakinen          #+#    #+#             */
/*   Updated: 2024/05/14 15:14:29 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdbool.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 256
# endif

typedef struct s_readbuf
{
	ssize_t	len;
	char	buf[BUFFER_SIZE];
}	t_readbuf;

typedef struct s_linebuf
{
	char	*buf;
	size_t	alloc;
	size_t	len;
}	t_linebuf;

void	*ft_memcpy(void *dst, const void *src, size_t n);

char	*get_next_line(int fd);

#endif
