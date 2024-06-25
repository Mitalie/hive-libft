/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   striter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 18:01:11 by amakinen          #+#    #+#             */
/*   Updated: 2024/04/25 18:08:23 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "testfw.h"
#include "libft.h"
#include <stdlib.h>
#include <string.h>

static void	check_str(char const *fn, char const *str, char const *match)
{
	if (match && !str)
		TEST_FAIL("%s returned null pointer, expected %s\n", fn, match);
	else if (str && !match)
		TEST_FAIL("%s returned %s, expected null pointer\n", fn, str);
	else if (str && strcmp(str, match))
		TEST_FAIL("%s returned wrong string \"%s\", expected \"%s\"\n",
			fn, str, match);
}

static char	map_addidx_mod26(unsigned int idx, char c)
{
	if (c >= 'a' && c <= 'z')
		c = 'a' + (c - 'a' + idx) % 26;
	else if (c >= 'A' && c <= 'Z')
		c = 'A' + (c - 'A' + idx) % 26;
	return (c);
}

REGISTER_TEST(ft_strmapi);

static void	test_ft_strmapi(void)
{
	char	*mapped;

	mapped = ft_strmapi("", map_addidx_mod26);
	check_str("ft_strmapi(\"\", map_addidx_mod26)", mapped, "");
	free(mapped);
	mapped = ft_strmapi("abcdEFGH", map_addidx_mod26);
	check_str("ft_strmapi(\"abcdEFGH\", map_addidx_mod26)", mapped, "acegIKMO");
	free(mapped);
}

static void	mut_addidx_mod26(unsigned int idx, char *cp)
{
	char	c;

	c = *cp;
	if (c >= 'a' && c <= 'z')
		c = 'a' + (c - 'a' + idx) % 26;
	else if (c >= 'A' && c <= 'Z')
		c = 'A' + (c - 'A' + idx) % 26;
	*cp = c;
}

REGISTER_TEST(ft_striteri);

static void	test_ft_striteri(void)
{
	char	buf[9];

	strcpy(buf, "");
	ft_striteri(buf, mut_addidx_mod26);
	check_str("ft_striteri(\"\", mut_addidx_mod26)", buf, "");
	strcpy(buf, "abcdEFGH");
	ft_striteri(buf, mut_addidx_mod26);
	check_str("ft_striteri(\"abcdEFGH\", mut_addidx_mod26)", buf, "acegIKMO");
}
