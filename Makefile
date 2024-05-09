# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/06 16:03:34 by amakinen          #+#    #+#              #
#    Updated: 2024/05/09 15:13:37 by amakinen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

_CFLAGS = -Wall -Wextra -Werror $(CFLAGS)
_CPPFLAGS = -MMD -MP -I./printf -I./test/ $(CPPFLAGS)
CC ?= cc
AR ?= ar

SRCS = $(wildcard test/*.c test/**/*.c)
OBJS = $(SRCS:.c=.o)
DEPS = $(OBJS:.o=.d)

ifneq (,$(SANITIZE))
    export CFLAGS := -g -fsanitize=$(SANITIZE) $(CFLAGS)
    export LDFLAGS := -fsanitize=$(SANITIZE) $(LDFLAGS)
endif

.PHONY: runtest all clean -clean fclean -fclean re

runtest: bin/test
	bin/test

all: bin/test

clean: printf/clean -clean
-clean:
	rm -f $(OBJS)
	rm -f $(DEPS)

fclean: printf/fclean -fclean
-fclean: -clean
	rm -f bin/test

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

bin/test: printf/libftprintf.a $(OBJS) | bin
	$(CC) $(LDFLAGS) $^ -o $@

bin:
	@mkdir -p $@

%.o: %.c
	$(CC) $(_CFLAGS) $(_CPPFLAGS) -c $< -o $@

-include $(DEPS)
