/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   internal.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 14:05:50 by amakinen          #+#    #+#             */
/*   Updated: 2024/07/08 14:06:46 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERNAL_H
# define INTERNAL_H

# include <stddef.h>
# include <limits.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 256
# endif

/*
	Modern Linux does not define OPEN_MAX. On Hive's Ubuntu workstations we have
	a soft limit of 1024 and hard limit of 1048576.
*/
# ifdef OPEN_MAX
#  define MY_OPEN_MAX OPEN_MAX
# else
#  define MY_OPEN_MAX 1048576
# endif

typedef struct s_buf
{
	char	*buf;
	size_t	alloc;
	size_t	len;
}	t_buf;

#endif
