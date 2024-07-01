# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test.mk                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/27 13:33:02 by amakinen          #+#    #+#              #
#    Updated: 2024/07/01 16:55:28 by amakinen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

TESTFW_DIRS = testfw base list
TESTFW_SRCS = $(wildcard $(patsubst %,test/%/*.c,$(TESTFW_DIRS)))
TESTFW_OBJS = $(TESTFW_SRCS:%.c=$(BUILDDIR)/%.o)
OBJS += $(TESTFW_OBJS)
$(TESTFW_OBJS): $(BUILDDIR)/%.o: %.c
$(TESTFW_OBJS): tgt_CPPFLAGS += -I test/include

TESTFW = $(BINDIR)/test/testfw
BINS += $(TESTFW)
$(TESTFW): $(TESTFW_OBJS) $(LIBFT)

SIMPLE_TEST_SRCS = $(wildcard test/base-simple/*.c)
SIMPLE_TEST_OBJS = $(SIMPLE_TEST_SRCS:%.c=$(BUILDDIR)/%.o)
OBJS += $(SIMPLE_TEST_OBJS)
$(SIMPLE_TEST_OBJS): $(BUILDDIR)/%.o: %.c

SIMPLE_TESTS = $(SIMPLE_TEST_SRCS:%.c=$(BINDIR)/%)
BINS += $(SIMPLE_TESTS)
$(SIMPLE_TESTS): $(BINDIR)/%: $(BUILDDIR)/%.o $(LIBFT)

.PHONY: test runtest

test: $(TESTFW) $(SIMPLE_TESTS)

runtest: $(TESTFW)
	$(TESTFW)

ifeq ($(shell uname -s),Linux)
# _GNU_SOURCE must be defined to get RTLD_NEXT from dlfcn.h
$(BUILDDIR)/test/testfw/mock_write.o: tgt_CPPFLAGS += -D_GNU_SOURCE
# strlcpy and strlcat are libbsd functions
$(BUILDDIR)/test/base/strl.o: tgt_CPPFLAGS += -DLIBBSD_OVERLAY -isystem /usr/include/bsd
# strnstr is a libbsd function
$(BUILDDIR)/test/base/strnstr.o: tgt_CPPFLAGS += -DLIBBSD_OVERLAY -isystem /usr/include/bsd
# link libbsd into the final binary
$(TESTFW): LDLIBS += -lbsd
endif
