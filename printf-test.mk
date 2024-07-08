# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    printf-test.mk                                     :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/05 13:33:23 by amakinen          #+#    #+#              #
#    Updated: 2024/07/08 13:50:56 by amakinen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

test/printf/gen/%.inc: test/printf/gen_%.sh
	$(mktargetdir)
	$< > $@

$(OBJDIR)/test/printf/bigtest_main.o: test/printf/gen/test_calls.inc test/printf/gen/test_flags.inc

PRINTF_TEST_SRCS = $(wildcard test/printf/*.c test/printf/**/*.c)
PRINTF_TEST_OBJS = $(PRINTF_TEST_SRCS:%.c=$(OBJDIR)/%.o)
OBJS += $(PRINTF_TEST_OBJS)
$(PRINTF_TEST_OBJS): tgt_CPPFLAGS += -I test/printf

PRINTF_TESTS = $(addprefix $(BINDIR)/test/printf/,test bigtest)
BINS += $(PRINTF_TESTS)
$(PRINTF_TESTS): $(BINDIR)/%: $(OBJDIR)/%_main.o $(filter-out %_main.o,$(PRINTF_TEST_OBJS)) $(LIBFT)

ifeq ($(shell uname -s),Linux)
    # _GNU_SOURCE must be defined to get asprintf from stdio.h before glibc 2.38
    $(OBJDIR)/test/printf/test_main.o $(OBJDIR)/test/printf/bigtest_main.o: CPPFLAGS += -D_GNU_SOURCE
    # _GNU_SOURCE must be defined to get RTLD_NEXT from dlfcn.h before glibc 2.36
    $(OBJDIR)/test/printf/utils/mock_write.o: CPPFLAGS += -D_GNU_SOURCE
endif

.PHONY: test runtest

test: $(PRINTF_TESTS)

runtest:: $(PRINTF_TESTS)
	$(filter %/test,$(PRINTF_TESTS))
	$(filter %/bigtest,$(PRINTF_TESTS))
