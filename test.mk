# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test.mk                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/27 13:33:02 by amakinen          #+#    #+#              #
#    Updated: 2024/06/27 15:28:24 by amakinen         ###   ########.fr        #
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

.PHONY: test runtest

test: $(TESTFW)

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
