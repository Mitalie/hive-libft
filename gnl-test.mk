# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    gnl-test.mk                                        :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/05 14:54:52 by amakinen          #+#    #+#              #
#    Updated: 2024/07/05 18:17:00 by amakinen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

GNL_TEST_SRCS = $(wildcard test/gnl/*.c)
GNL_TEST_OBJS = $(GNL_TEST_SRCS:%.c=$(OBJDIR)/%.o)
OBJS += $(GNL_TEST_OBJS)

GNL_TESTS = $(addprefix $(BINDIR)/test/gnl/,test nulltest twofiletest)
BINS += $(GNL_TESTS)
$(GNL_TESTS): $(BINDIR)/%: $(OBJDIR)/%_main.o $(filter-out %_main.o,$(GNL_TEST_OBJS)) $(LIBFT)

.PHONY: test runtest

test: $(GNL_TESTS)

runtest:: $(GNL_TESTS)
	cd test-data; ../$(filter %/test,$(GNL_TESTS))
	cd test-data; ../$(filter %/nulltest,$(GNL_TESTS))
	cd test-data; ../$(filter %/twofiletest,$(GNL_TESTS))
