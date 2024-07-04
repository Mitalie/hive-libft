/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:54:00 by amakinen          #+#    #+#             */
/*   Updated: 2024/04/17 16:01:22 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	main(int argc, char **argv)
{
	char	**pieces;

	if (argc < 2)
		return (1);
	pieces = ft_split(argv[1], ',');
	while (*pieces)
		ft_putendl_fd(*pieces++, 1);
}
