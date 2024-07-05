# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    printf-test.mk                                     :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/05 13:33:23 by amakinen          #+#    #+#              #
#    Updated: 2024/07/05 14:21:43 by amakinen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

printf-test/test/gen/%.inc: printf-test/test/gen_%.sh
	$(mktargetdir)
	$< > $@

printf-test/test/bigtest_main.c: printf-test/test/gen/test_calls.inc printf-test/test/gen/test_flags.inc

PRINTF_TEST_SRCS = $(wildcard printf-test/test/*.c printf-test/test/**/*.c)
PRINTF_TEST_OBJS = $(PRINTF_TEST_SRCS:%.c=$(OBJDIR)/%.o)
OBJS += $(PRINTF_TEST_OBJS)
$(PRINTF_TEST_OBJS): tgt_CPPFLAGS += -I printf -I printf-test/test

PRINTF_TESTS = $(addprefix $(BINDIR)/test/printf/,test bigtest)
BINS += $(PRINTF_TESTS)
$(PRINTF_TESTS): $(BINDIR)/test/printf/%: $(OBJDIR)/printf-test/test/%_main.o $(filter-out %_main.o,$(PRINTF_TEST_OBJS)) $(LIBFT)

ifeq ($(shell uname -s),Linux)
    # _GNU_SOURCE must be defined to get asprintf from stdio.h before glibc 2.38
    $(OBJDIR)/printf-test/test/test_main.o $(OBJDIR)/printf-test/test/bigtest_main.o: CPPFLAGS += -D_GNU_SOURCE
    # _GNU_SOURCE must be defined to get RTLD_NEXT from dlfcn.h before glibc 2.36
    $(OBJDIR)/printf-test/test/utils/mock_write.o: CPPFLAGS += -D_GNU_SOURCE
endif

.PHONY: test runtest

test: $(PRINTF_TESTS)

runtest:: $(PRINTF_TESTS)
	$(filter %/test,$(PRINTF_TESTS))
	$(filter %/bigtest,$(PRINTF_TESTS))
