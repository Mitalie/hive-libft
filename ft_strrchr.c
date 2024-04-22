/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 11:03:25 by amakinen          #+#    #+#             */
/*   Updated: 2024/04/22 16:47:10 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*found;

	found = 0;
	while (*s)
	{
		if (*s == c)
			found = (char *)s;
		s++;
	}
	if (*s == c)
		found = (char *)s;
	return (found);
}
