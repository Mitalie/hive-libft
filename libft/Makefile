# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/16 17:07:39 by amakinen          #+#    #+#              #
#    Updated: 2024/07/04 15:05:01 by amakinen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

BUILDDIR = build

_CFLAGS = -Wall -Wextra -Werror $(CFLAGS)
_CPPFLAGS = -MMD -MP $(CPPFLAGS)
CC ?= cc
AR ?= ar
mktargetdir = @mkdir -p $(@D)

NAME = libft.a

BASE_SRCS = \
	ft_isalpha.c \
	ft_isdigit.c \
	ft_isalnum.c \
	ft_isascii.c \
	ft_isprint.c \
	ft_strlen.c \
	ft_memset.c \
	ft_bzero.c \
	ft_memcpy.c \
	ft_memmove.c \
	ft_strlcpy.c \
	ft_strlcat.c \
	ft_toupper.c \
	ft_tolower.c \
	ft_strchr.c \
	ft_strrchr.c \
	ft_strncmp.c \
	ft_memchr.c \
	ft_memcmp.c \
	ft_strnstr.c \
	ft_atoi.c \
	ft_calloc.c \
	ft_strdup.c \
	ft_substr.c \
	ft_strjoin.c \
	ft_strtrim.c \
	ft_split.c \
	ft_itoa.c \
	ft_strmapi.c \
	ft_striteri.c \
	ft_putchar_fd.c \
	ft_putstr_fd.c \
	ft_putendl_fd.c \
	ft_putnbr_fd.c \

LIST_SRCS = \
	ft_lstnew.c \
	ft_lstadd_front.c \
	ft_lstsize.c \
	ft_lstlast.c \
	ft_lstadd_back.c \
	ft_lstdelone.c \
	ft_lstclear.c \
	ft_lstiter.c \
	ft_lstmap.c \

SRCS = $(BASE_SRCS) $(LIST_SRCS)
OBJS = $(SRCS:%.c=$(BUILDDIR)/%.o)
DEPS = $(OBJS:.o=.d)

# Inform make that .o files don't need to be remade if the actual target
# (e.g. libft.a) is up to date with respect to the source files.
.SECONDARY: $(OBJS)

.PHONY: all clean fclean re

all: $(NAME)

clean:
	rm -rf $(BUILDDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

$(NAME): $(OBJS)
	$(AR) -crs $@ $?

$(BUILDDIR)/%.o: %.c
	$(mktargetdir)
	$(CC) $(_CFLAGS) $(_CPPFLAGS) -c $< -o $@

-include $(DEPS)
