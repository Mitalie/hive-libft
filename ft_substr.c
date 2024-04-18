/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 14:27:42 by amakinen          #+#    #+#             */
/*   Updated: 2024/04/18 13:23:23 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	s_len;
	char	*sub;

	s += start;
	s_len = ft_strlen(s);
	if (s_len < len)
		len = s_len;
	sub = malloc(len + 1);
	if (sub)
	{
		ft_memcpy(sub, s, len);
		sub[len] = 0;
	}
	return (sub);
}
