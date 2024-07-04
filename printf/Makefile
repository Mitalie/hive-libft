# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/03 11:27:13 by amakinen          #+#    #+#              #
#    Updated: 2024/07/04 15:39:20 by amakinen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

BUILDDIR=build

_CFLAGS = -Wall -Wextra -Werror $(CFLAGS)
_CPPFLAGS = -MMD -MP -I./libft -I. $(CPPFLAGS)
CC ?= cc
AR ?= ar
mktargetdir = @mkdir -p $(@D)

NAME = libftprintf.a

SRCS = \
	ft_printf.c \
	util.c \
	padding_util.c \
	specifier.c \
	format_char.c \
	format_string.c \
	format_pointer.c \
	format_integer.c \

OBJS = $(SRCS:%.c=$(BUILDDIR)/%.o)
DEPS = $(OBJS:.o=.d)

# Inform make that .o files don't need to be remade if the actual target
# (e.g. libftprintf.a) is up to date with respect to the source files.
.SECONDARY: $(OBJS)

.PHONY: all clean -clean fclean -fclean re

all: $(NAME)

clean: libft/clean -clean
-clean:
	rm -rf $(BUILDDIR)

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

$(BUILDDIR)/%.o: %.c
	$(mktargetdir)
	$(CC) $(_CFLAGS) $(_CPPFLAGS) -c $< -o $@

-include $(DEPS)
