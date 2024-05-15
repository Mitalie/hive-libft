# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/13 15:49:44 by amakinen          #+#    #+#              #
#    Updated: 2024/05/14 15:03:05 by amakinen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

_CFLAGS = -Wall -Wextra -Werror $(CFLAGS)
_CPPFLAGS = -MMD -MP -I./gnl/ -I./test/ $(CPPFLAGS)
CC ?= cc
AR ?= ar

GNL_SRCS = gnl/get_next_line.c gnl/get_next_line_utils.c
SRCS = $(GNL_SRCS) $(wildcard test/*.c test/**/*.c)
OBJS = $(SRCS:.c=.o)
DEPS = $(OBJS:.o=.d)
BINS = bin/test

ifneq (,$(SANITIZE))
    export CFLAGS := -g -fsanitize=$(SANITIZE) $(CFLAGS)
    export LDFLAGS := -fsanitize=$(SANITIZE) $(LDFLAGS)
endif

.PHONY: runtest all clean fclean re

runtest: bin/test
	bin/test

all: $(BINS)

clean:
	rm -f $(OBJS)
	rm -f $(DEPS)
	rm -rf test/gen/

fclean: clean
	rm -f $(BINS)

re: fclean all

$(BINS): bin/%: test/%_main.o $(filter-out %_main.o,$(OBJS)) | bin
	$(CC) $(LDFLAGS) $^ -o $@

bin:
	@mkdir -p $@

%.o: %.c
	$(CC) $(_CFLAGS) $(_CPPFLAGS) -c $< -o $@

-include $(DEPS)
