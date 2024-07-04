# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/06 16:03:34 by amakinen          #+#    #+#              #
#    Updated: 2024/07/04 15:39:22 by amakinen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

BUILDDIR = build

_CFLAGS = -Wall -Wextra -Werror $(CFLAGS)
_CPPFLAGS = -MMD -MP -I./printf -I./test/ $(CPPFLAGS)
CC ?= cc
AR ?= ar
mktargetdir = @mkdir -p $(@D)

SRCS = $(wildcard test/*.c test/**/*.c)
OBJS = $(SRCS:%.c=$(BUILDDIR)/%.o)
DEPS = $(OBJS:.o=.d)
BINS = bin/test bin/bigtest

ifneq (,$(SANITIZE))
    export CFLAGS := -g -fsanitize=$(SANITIZE) $(CFLAGS)
    export LDFLAGS := -fsanitize=$(SANITIZE) $(LDFLAGS)
endif

# Inform make that .o files don't need to be remade if the actual targets
# (e.g. bin/test) are up to date with respect to the source files and libs.
.SECONDARY: $(OBJS)

.PHONY: runtest all clean -clean fclean -fclean re

runtest: bin/test bin/bigtest
	bin/test
	bin/bigtest

all: $(BINS)

clean: printf/clean -clean
-clean:
	rm -rf $(BUILDDIR)
	rm -rf test/gen/

fclean: printf/fclean -fclean
-fclean: -clean
	rm -f $(BINS)

re: fclean all

# Build any targets with printf/ prefix with recursive make
printf/clean printf/fclean printf/libftprintf.a: printf/%:
	+make -C printf $*

# We must always execute the recursive make as this Makefile doesn't know
# whether the recursive target needs updating, but printf/libftprintf.a must not
# be marked as a phony target directly or its dependents will get rebuilt
# regardless of whether it changed or not.
.PHONY: printf/clean printf/fclean phony
printf/libftprintf.a: phony

test/gen/%.inc: test/gen_%.sh
	$(mktargetdir)
	$< > $@

test/bigtest_main.c: test/gen/test_calls.inc test/gen/test_flags.inc

$(BINS): bin/%: $(BUILDDIR)/test/%_main.o $(filter-out %_main.o,$(OBJS)) printf/libftprintf.a
	$(mktargetdir)
	$(CC) $(LDFLAGS) $^ -o $@

$(BUILDDIR)/%.o: %.c
	$(mktargetdir)
	$(CC) $(_CFLAGS) $(_CPPFLAGS) -c $< -o $@

ifeq ($(shell uname -s),Linux)
# _GNU_SOURCE must be defined to get asprintf from stdio.h before glibc 2.38
$(BUILDDIR)/test/test_main.o $(BUILDDIR)/test/bigtest_main.o: CPPFLAGS += -D_GNU_SOURCE
# _GNU_SOURCE must be defined to get RTLD_NEXT from dlfcn.h before glibc 2.36
$(BUILDDIR)/test/utils/mock_write.o: CPPFLAGS += -D_GNU_SOURCE
endif

# Use cflow to generate function dependency graphs in dot format (which can then
# be rendered with graphviz or online tools). To make the graph more readable,
# use sed to remove extra label text and add formatting settings.
graph.dot: # printf/**/*.c
	cflow printf/libft/*.c printf/*.c -m ft_printf -f dot | sed \
		-e '/\[label=".*"\]/d' \
		-e '/\[label="/,/"\]$$/d' \
		-e '2{p;s/.*/    graph [pad="0.5", nodesep="1", ranksep="2"]/;}' > graph.dot

-include $(DEPS)
