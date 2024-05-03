# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/16 17:07:39 by amakinen          #+#    #+#              #
#    Updated: 2024/04/26 17:53:35 by amakinen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS += -Wall -Wextra -Werror
CPPFLAGS += -MMD -MP
CC ?= cc
AR ?= ar

NAME = libft.a

SRCS = \
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

BONUS_SRCS = \
	ft_lstnew_bonus.c \
	ft_lstadd_front_bonus.c \
	ft_lstsize_bonus.c \
	ft_lstlast_bonus.c \
	ft_lstadd_back_bonus.c \
	ft_lstdelone_bonus.c \
	ft_lstclear_bonus.c \
	ft_lstiter_bonus.c \
	ft_lstmap_bonus.c \

OBJS = $(SRCS:.c=.o)
BONUS_OBJS = $(BONUS_SRCS:.c=.o)
DEPS = $(OBJS:.o=.d) $(BONUS_OBJS:.o=.d)

.PHONY: all clean fclean re bonus

all: $(NAME)

clean:
	rm -f $(OBJS) $(BONUS_OBJS)
	rm -f $(DEPS)

fclean: clean
	rm -f $(NAME)

re: fclean all

$(NAME): $(OBJS)
	$(AR) -crs $@ $?

# Bonus doesn't create a its own target file which make could use to determine
# whether the it needs updating, so instead we target a dummy archive member
# which specifies the actual dependencies and the ar recipe.
bonus: $(NAME)(.bonus-timestamp)

# Order-only dependency on the non-bonus part ensures make can't corrupt the
# archive by executing both ar recipes modifying it simultaneously.
$(NAME)(.bonus-timestamp): $(BONUS_OBJS) | $(NAME)
	@touch .bonus-timestamp
	$(AR) -crs $(NAME) .bonus-timestamp $?
	@rm .bonus-timestamp

%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

-include $(DEPS)
