/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testfw_mock_write.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 16:43:07 by amakinen          #+#    #+#             */
/*   Updated: 2024/06/24 19:22:00 by amakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTFW_MOCK_WRITE_H
# define TESTFW_MOCK_WRITE_H

# include <stddef.h>

void	testfw_mock_write(int fildes);
size_t	testfw_unmock_write(int fildes, void **buf);
void	testfw_unmock_write_check(int fildes, char *fn,
			const void *exp_data, size_t exp_len);

#endif
