/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 15:03:45 by amakinen          #+#    #+#             */
/*   Updated: 2024/05/16 14:41:16 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <unistd.h>
# include <stdbool.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 256
# endif

typedef struct s_readbuf
{
	char	*buf;
	size_t	len;
	bool	prev_nullterm;
}	t_readbuf;

typedef struct s_linebuf
{
	char	*buf;
	size_t	alloc;
	size_t	len;
}	t_linebuf;

void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_reallocf(void *old_alloc, size_t new_size, size_t old_data_len);
char	*bufs_to_str(const char *b1, size_t l1, const char *b2, size_t l2);
void	*cleanup(t_linebuf *line, t_readbuf *readbuf);

char	*get_next_line(int fd);

#endif
