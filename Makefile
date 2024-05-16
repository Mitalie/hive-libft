# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/13 15:49:44 by amakinen          #+#    #+#              #
#    Updated: 2024/05/16 16:05:13 by amakinen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

_CFLAGS = -Wall -Wextra -Werror $(CFLAGS)
_CPPFLAGS = -MMD -MP -I./gnl/ -I./test/ $(CPPFLAGS)
CC ?= cc
AR ?= ar

GNL_SRCS = gnl/get_next_line.c gnl/get_next_line_utils.c
GNL_OBJS = $(GNL_SRCS:.c=.o)
GNLB_SRCS = gnl/get_next_line_bonus.c gnl/get_next_line_utils_bonus.c
GNLB_OBJS = $(GNLB_SRCS:.c=.o)
SRCS = $(wildcard test/*.c test/**/*.c)
OBJS = $(SRCS:.c=.o) $(GNL_OBJS) $(GNLB_OBJS)
DEPS = $(OBJS:.o=.d)
BINS = bin/test
B_BINS = bin/bonustest

ifneq (,$(SANITIZE))
    export CFLAGS := -g -fsanitize=$(SANITIZE) $(CFLAGS)
    export LDFLAGS := -fsanitize=$(SANITIZE) $(LDFLAGS)
endif

.PHONY: runtest all clean fclean re

runtest: bin/test bin/bonustest
	bin/test
	bin/bonustest

all: $(BINS) $(B_BINS)

clean:
	rm -f $(OBJS)
	rm -f $(DEPS)
	rm -rf test/gen/

fclean: clean
	rm -f $(BINS)

re: fclean all

$(BINS): bin/%: test/%_main.o $(GNL_OBJS) | bin
	$(CC) $(LDFLAGS) $^ -o $@

$(B_BINS): bin/%: test/%_main.o $(GNLB_OBJS) | bin
	$(CC) $(LDFLAGS) $^ -o $@

bin:
	@mkdir -p $@

%.o: %.c
	$(CC) $(_CFLAGS) $(_CPPFLAGS) -c $< -o $@

-include $(DEPS)
