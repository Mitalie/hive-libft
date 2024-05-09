# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/03 11:27:13 by amakinen          #+#    #+#              #
#    Updated: 2024/05/09 12:13:36 by amakinen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

_CFLAGS = -Wall -Wextra -Werror $(CFLAGS)
_CPPFLAGS = -MMD -MP -I./libft -I. $(CPPFLAGS)
CC ?= cc
AR ?= ar

NAME = libftprintf.a

SRCS = \
	ft_printf.c \
	calculate_padding.c \
	writers.c \
	num_str_util.c \
	parse_specifier.c \
	formatters/char.c \
	formatters/string.c \
	formatters/pointer.c \
	formatters/integer.c \

OBJS = $(SRCS:.c=.o)
DEPS = $(OBJS:.o=.d)

.PHONY: all bonus clean -clean fclean -fclean re

all: $(NAME)

# The same ft_printf function meets both mandatory and bonus requirements, so
# there are no separate bonus files to build.
bonus: $(NAME)

clean: libft/clean -clean
-clean:
	rm -f $(OBJS)
	rm -f $(DEPS)

fclean: libft/fclean -fclean
-fclean: -clean
	rm -f $(NAME)

re: fclean all

# Build any targets with libft/ prefix with recursive make
libft/clean libft/fclean libft/libft.a: libft/%:
	+make -C libft $*

# We must always execute the recursive make as this Makefile doesn't know
# whether the recursive target needs updating, but libft/libft.a must not be
# marked as a phony target directly or its dependents will get rebuilt
# regardless of whether it changed or not.
.PHONY: libft/clean libft/fclean phony
libft/libft.a: phony

$(NAME): libft/libft.a $(OBJS)
	cp libft/libft.a $@
	$(AR) -crs $@ $(OBJS)

%.o: %.c
	$(CC) $(_CFLAGS) $(_CPPFLAGS) -c $< -o $@

-include $(DEPS)
