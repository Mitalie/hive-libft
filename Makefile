# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/16 17:07:39 by amakinen          #+#    #+#              #
#    Updated: 2024/04/16 17:54:36 by amakinen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRCS = \

OBJS = $(SRCS:.c=.o)

CFLAGS += -Wall -Wextra -Werror
CC ?= cc
AR ?= ar

.PHONY: all clean fclear re

all: $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

$(NAME): $(OBJS)
	$(AR) -crs $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@
