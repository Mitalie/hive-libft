# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/13 15:49:44 by amakinen          #+#    #+#              #
#    Updated: 2024/07/04 11:56:46 by amakinen         ###   ########.fr        #
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
GNLB_SRCS = gnl/get_next_line_bonus.c gnl/get_next_line_utils_bonus.c
GNLB_OBJS = $(GNLB_SRCS:%.c=$(BUILDDIR)/%.o)
SRCS = $(wildcard test/*.c test/**/*.c)
OBJS = $(SRCS:%.c=$(BUILDDIR)/%.o) $(GNL_OBJS) $(GNLB_OBJS)
DEPS = $(OBJS:.o=.d)
BINS = bin/test bin/nulltest
B_BINS = bin/bonustest bin/bnulltest

ifneq (,$(SANITIZE))
    export CFLAGS := -g -fsanitize=$(SANITIZE) $(CFLAGS)
    export LDFLAGS := -fsanitize=$(SANITIZE) $(LDFLAGS)
endif

.PHONY: runtest all clean fclean re

runtest: bin/test bin/nulltest bin/bonustest bin/bnulltest
	bin/test
	bin/nulltest
	bin/bonustest
	bin/bnulltest

all: $(BINS) $(B_BINS)

clean:
	rm -rf $(BUILDDIR)

fclean: clean
	rm -f $(BINS) $(B_BINS)

re: fclean all

$(BINS): bin/%: $(BUILDDIR)/test/%_main.o $(GNL_OBJS)
	$(mktargetdir)
	$(CC) $(LDFLAGS) $^ -o $@

$(B_BINS): bin/%: $(BUILDDIR)/test/%_main.o $(GNLB_OBJS)
	$(mktargetdir)
	$(CC) $(LDFLAGS) $^ -o $@

$(BUILDDIR)/%.o: %.c
	$(mktargetdir)
	$(CC) $(_CFLAGS) $(_CPPFLAGS) -c $< -o $@

-include $(DEPS)
