# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/17 16:58:00 by amakinen          #+#    #+#              #
#    Updated: 2024/04/24 11:14:38 by amakinen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS += -Wall -Wextra -Werror
CPPFLAGS += -MMD -MP -I../libft
LIBFT = ../libft/libft.a
CC ?= cc
AR ?= ar

BINDIR = bin
TESTFW = $(BINDIR)/testfw

SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)
DEPS = $(OBJS:.o=.d)

TESTFW_OBJS = $(filter testfw%,$(OBJS))
SIMPLE_TESTS = $(patsubst %.c,$(BINDIR)/%,$(wildcard test_*.c))
TESTS = $(SIMPLE_TESTS) $(TESTFW)

.PHONY: all clean fclean re

all: $(TESTS)

clean:
	rm -f $(OBJS)
	rm -f $(DEPS)

fclean: clean
	rm -f $(TESTS)

re: fclean all

$(BINDIR):
	@mkdir -p $@

$(TESTFW): $(TESTFW_OBJS) $(LIBFT) | $(BINDIR)
	$(CC) $(LDFLAGS) $^ -o $@

$(SIMPLE_TESTS): $(BINDIR)/%: %.o $(LIBFT) | $(BINDIR)
	$(CC) $(LDFLAGS) $^ -o $@

$(OBJS): %.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

-include $(DEPS)
