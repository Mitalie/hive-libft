# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/17 16:58:00 by amakinen          #+#    #+#              #
#    Updated: 2024/04/19 14:20:28 by amakinen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SUBDIR = libft/
include libft/Makefile
SUBDIR =

.PHONY: all clean tclean fclean tfclean test

TEST_SRCS = $(wildcard test/ft_*.c)
TEST_OBJS = $(TEST_SRCS:.c=.o)
TESTS = $(TEST_SRCS:.c=.test)

all: $(TESTS)

clean: tclean
tclean:
	rm -f $(TEST_OBJS)

fclean: tfclean
tfclean:
	rm -f $(TESTS)

test/%.test: test/%.o libft/libft.a
	$(CC) $(CFLAGS) $^ -o $@

$(TEST_OBJS): %.o: %.c
	$(CC) $(CFLAGS) -Ilibft -c $^ -o $@
