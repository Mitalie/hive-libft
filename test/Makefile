# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/17 16:58:00 by amakinen          #+#    #+#              #
#    Updated: 2024/06/25 14:25:08 by amakinen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS += -Wall -Wextra -Werror
CPPFLAGS += -MMD -MP -I ../libft -I include
LIBFT = ../libft/libft.a
CC ?= cc
AR ?= ar

BINDIR = bin
TESTFW = $(BINDIR)/testfw

SRCS = $(wildcard */*.c)
OBJS = $(SRCS:.c=.o)
DEPS = $(OBJS:.o=.d)

TESTFW_OBJS = $(filter testfw/% base/% list/%,$(OBJS))
SIMPLE_TESTS = $(patsubst base-simple/%.c,$(BINDIR)/%,$(wildcard base-simple/*.c))
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
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(SIMPLE_TESTS): $(BINDIR)/%: base-simple/%.o $(LIBFT) | $(BINDIR)
	$(CC) $(LDFLAGS) $^ -o $@

$(OBJS): %.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

ifeq ($(shell uname -s),Linux)
# _GNU_SOURCE must be defined to get RTLD_NEXT from dlfcn.h
testfw/mock_write.o: CPPFLAGS += -D_GNU_SOURCE
# strlcpy and strlcat are libbsd functions
base/strl.o: CPPFLAGS += -DLIBBSD_OVERLAY -isystem /usr/include/bsd
# strnstr is a libbsd function
base/strnstr.o: CPPFLAGS += -DLIBBSD_OVERLAY -isystem /usr/include/bsd
# link libbsd into the final binary
$(TESTFW): LDLIBS += -lbsd
endif

-include $(DEPS)
