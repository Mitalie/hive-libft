/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:54:00 by amakinen          #+#    #+#             */
/*   Updated: 2024/07/08 12:57:11 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

int	main(int argc, char **argv)
{
	char	**pieces;
	char	**orig;

	if (argc < 2)
		return (1);
	pieces = ft_split(argv[1], ',');
	orig = pieces;
	while (*pieces)
	{
		ft_putendl_fd(*pieces, 1);
		free(*pieces++);
	}
	free(orig);
}
