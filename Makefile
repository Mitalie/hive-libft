# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/23 10:50:25 by amakinen          #+#    #+#              #
#    Updated: 2024/04/23 15:36:21 by amakinen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

DIRS = libft test

.PHONY: all clean fclean re $(DIRS) runtest

runtest: test
	test/bin/testfw

all: $(DIRS)

$(DIRS):
	+make -C $@

test: libft

clean: $(addsuffix -clean,$(DIRS))
%-clean:
	+make -C $* clean

fclean: $(addsuffix -fclean,$(DIRS))
%-fclean:
	+make -C $* fclean

re: fclean all
