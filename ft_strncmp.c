/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 11:18:44 by amakinen          #+#    #+#             */
/*   Updated: 2024/04/17 11:32:05 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int	cmp;

	cmp = 0;
	while (*s1 && cmp && n--)
		cmp = (unsigned char)*s1++ - (unsigned char)*s2++;
	return (cmp);
}
