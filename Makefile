# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/03 11:27:13 by amakinen          #+#    #+#              #
#    Updated: 2024/05/17 14:13:22 by amakinen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

_CFLAGS = -Wall -Wextra -Werror $(CFLAGS)
_CPPFLAGS = -MMD -MP -I./libft -I. $(CPPFLAGS)
CC ?= cc
AR ?= ar

NAME = libftprintf.a

SRCS_SHARED = \
	ft_printf.c \
	util_shared.c \

SRCS_MANDATORY = \
	mandatory/specifier.c \
	mandatory/format_char.c \
	mandatory/format_string.c \
	mandatory/format_pointer.c \
	mandatory/format_integer.c \

SRCS_BONUS = \
	bonus/util_bonus.c \
	bonus/specifier_bonus.c \
	bonus/format_char_bonus.c \
	bonus/format_string_bonus.c \
	bonus/format_pointer_bonus.c \
	bonus/format_integer_bonus.c \

OBJ_SHARED = $(SRCS_SHARED:.c=.o)
OBJ_MANDATORY = $(SRCS_MANDATORY:.c=.o)
OBJ_BONUS = $(SRCS_BONUS:.c=.o)
OBJS = $(OBJ_SHARED) $(OBJ_MANDATORY) $(OBJ_BONUS)
DEPS = $(OBJS:.o=.d)

.PHONY: all bonus clean -clean fclean -fclean re

all: $(NAME)

$(NAME): $(NAME)(.nobonus)

bonus: $(NAME)(.bonus)

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

$(NAME)(.nobonus): libft/libft.a $(OBJ_SHARED) $(OBJ_MANDATORY)
	cp libft/libft.a $(NAME)
	@touch .nobonus
	$(AR) -crs $(NAME) .nobonus $(OBJ_SHARED) $(OBJ_MANDATORY)
	@rm .nobonus

$(NAME)(.bonus): libft/libft.a $(OBJ_SHARED) $(OBJ_BONUS)
	cp libft/libft.a $(NAME)
	@touch .bonus
	$(AR) -crs $(NAME) .bonus $(OBJ_SHARED) $(OBJ_BONUS)
	@rm .bonus

%.o: %.c
	$(CC) $(_CFLAGS) $(_CPPFLAGS) -c $< -o $@

-include $(DEPS)
