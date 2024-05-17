# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/06 16:03:34 by amakinen          #+#    #+#              #
#    Updated: 2024/05/17 13:00:20 by amakinen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

_CFLAGS = -Wall -Wextra -Werror $(CFLAGS)
_CPPFLAGS = -MMD -MP -I./printf -I./test/ $(CPPFLAGS)
CC ?= cc
AR ?= ar

SRCS = $(wildcard test/*.c test/**/*.c)
OBJS = $(SRCS:.c=.o)
DEPS = $(OBJS:.o=.d)
BINS = bin/test bin/bigtest

ifneq (,$(SANITIZE))
    export CFLAGS := -g -fsanitize=$(SANITIZE) $(CFLAGS)
    export LDFLAGS := -fsanitize=$(SANITIZE) $(LDFLAGS)
endif

.PHONY: runtest all clean -clean fclean -fclean re

runtest: bin/test bin/bigtest
	bin/test
	bin/bigtest

all: $(BINS)

clean: printf/clean -clean
-clean:
	rm -f $(OBJS)
	rm -f $(DEPS)
	rm -rf test/gen/

fclean: printf/fclean -fclean
-fclean: -clean
	rm -f $(BINS)

re: fclean all

# Build any targets with printf/ prefix with recursive make
printf/clean printf/fclean: printf/%:
	+make -C printf $*

# Tests require bonus functionality
 printf/libftprintf.a:
	+make -C printf bonus

# We must always execute the recursive make as this Makefile doesn't know
# whether the recursive target needs updating, but printf/libftprintf.a must not
# be marked as a phony target directly or its dependents will get rebuilt
# regardless of whether it changed or not.
.PHONY: printf/clean printf/fclean phony
printf/libftprintf.a: phony

test/gen/%.inc: test/gen_%.sh | test/gen
	$< > $@

test/bigtest_main.c: test/gen/test_calls.inc test/gen/test_flags.inc

$(BINS): bin/%: test/%_main.o $(filter-out %_main.o,$(OBJS)) printf/libftprintf.a | bin
	$(CC) $(LDFLAGS) $^ -o $@

test/gen bin:
	@mkdir -p $@

%.o: %.c
	$(CC) $(_CFLAGS) $(_CPPFLAGS) -c $< -o $@

-include $(DEPS)
