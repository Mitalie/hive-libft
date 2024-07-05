# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    gnl-test.mk                                        :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/05 14:54:52 by amakinen          #+#    #+#              #
#    Updated: 2024/07/05 15:05:11 by amakinen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

GNL_TEST_SRCS = $(wildcard gnl-test/test/*.c gnl-test/test/**/*.c)
GNL_TEST_OBJS = $(GNL_TEST_SRCS:%.c=$(OBJDIR)/%.o)
OBJS += $(GNL_TEST_OBJS)
$(GNL_TEST_OBJS): tgt_CPPFLAGS += -I gnl

GNL_TESTS = $(addprefix $(BINDIR)/test/gnl/,test nulltest twofiletest)
BINS += $(GNL_TESTS)
$(GNL_TESTS): $(BINDIR)/test/gnl/%: $(OBJDIR)/gnl-test/test/%_main.o $(filter-out %_main.o,$(GNL_TEST_OBJS)) $(LIBFT)

.PHONY: test runtest

test: $(GNL_TESTS)

runtest:: $(GNL_TESTS)
	cd gnl-test; ../$(filter %/test,$(GNL_TESTS))
	cd gnl-test; ../$(filter %/nulltest,$(GNL_TESTS))
	cd gnl-test; ../$(filter %/twofiletest,$(GNL_TESTS))
