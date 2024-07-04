# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/13 15:49:44 by amakinen          #+#    #+#              #
#    Updated: 2024/07/04 16:04:01 by amakinen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

BUILDDIR = build

_CFLAGS = -Wall -Wextra -Werror $(CFLAGS)
_CPPFLAGS = -MMD -MP -I./gnl/ -I./test/ $(CPPFLAGS)
CC ?= cc
AR ?= ar
mktargetdir = @mkdir -p $(@D)

GNL_SRCS = gnl/get_next_line.c gnl/get_next_line_utils.c
GNL_OBJS = $(GNL_SRCS:%.c=$(BUILDDIR)/%.o)
SRCS = $(wildcard test/*.c test/**/*.c)
OBJS = $(SRCS:%.c=$(BUILDDIR)/%.o) $(GNL_OBJS)
DEPS = $(OBJS:.o=.d)
BINS = bin/test bin/nulltest bin/twofiletest

ifneq (,$(SANITIZE))
    export CFLAGS := -g -fsanitize=$(SANITIZE) $(CFLAGS)
    export LDFLAGS := -fsanitize=$(SANITIZE) $(LDFLAGS)
endif

# Inform make that .o files don't need to be remade if the actual targets
# are up to date with respect to the source files.
.SECONDARY: $(OBJS)

.PHONY: runtest all clean fclean re

runtest: bin/test bin/nulltest bin/twofiletest
	bin/test
	bin/nulltest
	bin/twofiletest

all: $(BINS)

clean:
	rm -rf $(BUILDDIR)

fclean: clean
	rm -f $(BINS) $(B_BINS)

re: fclean all

$(BINS): bin/%: $(BUILDDIR)/test/%_main.o $(GNL_OBJS)
	$(mktargetdir)
	$(CC) $(LDFLAGS) $^ -o $@

$(BUILDDIR)/%.o: %.c
	$(mktargetdir)
	$(CC) $(_CFLAGS) $(_CPPFLAGS) -c $< -o $@

-include $(DEPS)
