/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 15:45:20 by amakinen          #+#    #+#             */
/*   Updated: 2024/05/28 10:58:29 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stddef.h>
# include <stdbool.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 256
# endif

typedef struct s_buf
{
	char	*buf;
	size_t	alloc;
	size_t	len;
}	t_buf;

void	*ft_memcpy(void *dst, const void *src, size_t n);

char	*get_next_line(int fd);

#endif
