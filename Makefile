# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/17 16:58:00 by amakinen          #+#    #+#              #
#    Updated: 2024/04/19 18:08:09 by amakinen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SUBDIR = libft/
include libft/Makefile
SUBDIR =

.PHONY: all clean tclean fclean tfclean tre test

TEST_SRCS = $(wildcard test/*.c)
TEST_OBJS = $(TEST_SRCS:.c=.o)
TESTS = $(patsubst test/%.c,bin/%,$(wildcard test/test_*.c))

all: $(TESTS)

clean: tclean
tclean:
	rm -f $(TEST_OBJS)

fclean: tfclean
tfclean: tclean
	rm -f $(TESTS)

tre: tfclean all

testbin:
	@mkdir -p bin

bin/%: test/%.o libft/libft.a | testbin
	$(CC) $(CFLAGS) $^ -o $@

$(TEST_OBJS): %.o: %.c
	$(CC) $(CFLAGS) -Ilibft -c $^ -o $@
