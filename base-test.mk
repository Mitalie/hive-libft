# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    base-test.mk                                       :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/05 13:06:32 by amakinen          #+#    #+#              #
#    Updated: 2024/07/05 13:39:38 by amakinen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SIMPLE_TEST_SRCS = $(wildcard libft-test/test/base-simple/*.c)
SIMPLE_TEST_OBJS = $(SIMPLE_TEST_SRCS:%.c=$(OBJDIR)/%.o)

OBJS += $(SIMPLE_TEST_OBJS)
$(SIMPLE_TEST_OBJS): tgt_CPPFLAGS += -I libft

SIMPLE_TESTS = $(SIMPLE_TEST_SRCS:libft-test/%.c=$(BINDIR)/%)
BINS += $(SIMPLE_TESTS)
$(SIMPLE_TESTS): $(BINDIR)/%: $(OBJDIR)/libft-test/%.o $(LIBFT)

.PHONY: test runtest-base-simple

test: $(SIMPLE_TESTS)

# Exclude these from the runtest target as testfw also covers them
runtest-base-simple: $(SIMPLE_TESTS)
	$(filter %/test_putnbr,$(SIMPLE_TESTS))
	$(filter %/test_atoi,$(SIMPLE_TESTS)) ""
	$(filter %/test_atoi,$(SIMPLE_TESTS)) -
	$(filter %/test_atoi,$(SIMPLE_TESTS)) 999999999
	$(filter %/test_atoi,$(SIMPLE_TESTS)) 9999999999
	$(filter %/test_atoi,$(SIMPLE_TESTS)) 999999999999999999
	$(filter %/test_atoi,$(SIMPLE_TESTS)) 9999999999999999999
	$(filter %/test_atoi,$(SIMPLE_TESTS)) -999999999
	$(filter %/test_atoi,$(SIMPLE_TESTS)) -9999999999
	$(filter %/test_atoi,$(SIMPLE_TESTS)) -999999999999999999
	$(filter %/test_atoi,$(SIMPLE_TESTS)) -9999999999999999999
	$(filter %/test_split,$(SIMPLE_TESTS)) a,b,cd,e
	$(filter %/test_split,$(SIMPLE_TESTS)) a,,,b,cd,e,,,,
