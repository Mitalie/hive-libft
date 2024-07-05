# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    testfw.mk                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/05 13:00:29 by amakinen          #+#    #+#              #
#    Updated: 2024/07/05 13:30:30 by amakinen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

TESTFW_DIRS = testfw base list
TESTFW_SRCS = $(wildcard $(patsubst %,libft-test/test/%/*.c,$(TESTFW_DIRS)))

TESTFW_OBJS = $(TESTFW_SRCS:%.c=$(OBJDIR)/%.o)
$(TESTFW_OBJS): tgt_CPPFLAGS += -I libft -I libft-test/test/include
OBJS += $(TESTFW_OBJS)

TESTFW = $(BINDIR)/test/testfw
BINS += $(TESTFW)
$(TESTFW): $(TESTFW_OBJS) $(LIBFT)

ifeq ($(shell uname -s),Linux)
    # _GNU_SOURCE must be defined to get RTLD_NEXT from dlfcn.h before glibc 2.36
    $(OBJDIR)/libft-test/test/testfw/mock_write.o: tgt_CPPFLAGS += -D_GNU_SOURCE
    # strlcpy and strlcat don't exist in glibc before 2.38, use libbsd
    $(OBJDIR)/libft-test/test/base/strl.o: tgt_CPPFLAGS += -DLIBBSD_OVERLAY -isystem /usr/include/bsd
    # strnstr doesn't exist in glibc, use libbsd
    $(OBJDIR)/libft-test/test/base/strnstr.o: tgt_CPPFLAGS += -DLIBBSD_OVERLAY -isystem /usr/include/bsd
    # link libbsd into the binary
    $(TESTFW): tgt_LDLIBS += -lbsd
endif

.PHONY: test runtest

test: $(TESTFW)

runtest:: $(TESTFW)
	$(TESTFW)
