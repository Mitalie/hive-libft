# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/03 11:27:13 by amakinen          #+#    #+#              #
#    Updated: 2024/05/07 11:13:40 by amakinen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS += -Wall -Wextra -Werror
CPPFLAGS += -MMD -MP -I./libft -I.
CC ?= cc
AR ?= ar

NAME = libftprintf.a

SRCS = \
	ft_printf.c \
	check_write.c \
	num_str_util.c \
	formatters/char.c \
	formatters/string.c \
	formatters/pointer.c \
	formatters/integer.c \

OBJS = $(SRCS:.c=.o)
DEPS = $(OBJS:.o=.d)

.PHONY: all clean fclean re libft

all: $(NAME)

clean:
	rm -f $(OBJS)
	rm -f $(DEPS)

fclean: clean
	rm -f $(NAME)

re: fclean all

# We need to call recursive make in a phony target since top level Make doesn't
# know the subdirectory's dependencies and won't notice if they change. But if
# our real target depends directly on a phony target, it is always rebuilt as
# the phony dependency doesn't have a timestamp to determine it didn't change.
# By having an intermediate real target that depends on the phony target, and
# defining a(n empty) recipe for that real target, Make will build the phony
# target, execute the recipe, and then check timestamps to determine if the
# dependent targets need to be updated.
libft:
	+make -C libft

libft/libft.a: libft
	@

$(NAME): libft/libft.a $(OBJS)
	cp libft/libft.a $@
	$(AR) -crs $@ $(filter-out libft/libft.a,$^)

%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

-include $(DEPS)
