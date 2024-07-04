# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/23 10:50:25 by amakinen          #+#    #+#              #
#    Updated: 2024/04/26 15:36:23 by amakinen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

DIRS = libft test

.PHONY: all clean fclean re $(DIRS) runtest

ifneq (,$(SANITIZE))
    export CFLAGS += -g -fsanitize=$(SANITIZE)
    export LDFLAGS += -fsanitize=$(SANITIZE)
endif

runtest: test
	test/bin/testfw

all: $(DIRS)

libft:
	+make -C $@ bonus

test: libft
	+make -C $@

clean: $(addsuffix -clean,$(DIRS))
%-clean:
	+make -C $* clean

fclean: $(addsuffix -fclean,$(DIRS))
%-fclean:
	+make -C $* fclean

re: fclean all
