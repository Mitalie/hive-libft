# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    base.mk                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amakinen <amakinen@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/05 12:54:43 by amakinen          #+#    #+#              #
#    Updated: 2024/07/05 17:50:39 by amakinen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

BASE_SRCS = $(addprefix src/base/,\
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
)

BASE_OBJS = $(BASE_SRCS:%.c=$(OBJDIR)/%.o)
OBJS += $(BASE_OBJS)

LIBFT = $(LIBDIR)/libft.a
LIBS += $(LIBFT)
$(LIBFT): $(BASE_OBJS)
