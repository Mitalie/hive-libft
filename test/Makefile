# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/17 16:58:00 by amakinen          #+#    #+#              #
#    Updated: 2024/06/26 12:24:01 by amakinen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS += -Wall -Wextra -Werror
CPPFLAGS += -MMD -MP -I ../libft -I include
LIBFT = ../libft/libft.a
CC ?= cc
AR ?= ar
mktargetdir = @mkdir -p $(@D)

BINDIR = bin
BUILDDIR = build
TESTFW = $(BINDIR)/testfw

SRCS = $(wildcard */*.c)
OBJS = $(SRCS:%.c=$(BUILDDIR)/%.o)
DEPS = $(OBJS:.o=.d)

TESTFW_OBJS = $(filter $(BUILDDIR)/testfw/% $(BUILDDIR)/base/% $(BUILDDIR)/list/%,$(OBJS))
SIMPLE_TESTS = $(patsubst base-simple/%.c,$(BINDIR)/%,$(wildcard base-simple/*.c))
TESTS = $(SIMPLE_TESTS) $(TESTFW)

.PHONY: all clean fclean re

all: $(TESTS)

clean:
	rm -rf $(BUILDDIR)

fclean: clean
	rm -rf $(BINDIR)

re: fclean all

$(TESTFW): $(TESTFW_OBJS) $(LIBFT)
	$(mktargetdir)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(SIMPLE_TESTS): $(BINDIR)/%: $(BUILDDIR)/base-simple/%.o $(LIBFT)
	$(mktargetdir)
	$(CC) $(LDFLAGS) $^ -o $@

$(OBJS): $(BUILDDIR)/%.o: %.c
	$(mktargetdir)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

ifeq ($(shell uname -s),Linux)
# _GNU_SOURCE must be defined to get RTLD_NEXT from dlfcn.h
$(BUILDDIR)/testfw/mock_write.o: CPPFLAGS += -D_GNU_SOURCE
# strlcpy and strlcat are libbsd functions
$(BUILDDIR)/base/strl.o: CPPFLAGS += -DLIBBSD_OVERLAY -isystem /usr/include/bsd
# strnstr is a libbsd function
$(BUILDDIR)/base/strnstr.o: CPPFLAGS += -DLIBBSD_OVERLAY -isystem /usr/include/bsd
# link libbsd into the final binary
$(TESTFW): LDLIBS += -lbsd
endif

-include $(DEPS)
